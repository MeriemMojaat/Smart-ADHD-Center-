#include "smtp.h"
// This function initializes an SMTP client with the specified credentials and server information
// Parameters:
// - user: the username for SMTP authentication
// - pass: the password for SMTP authentication
// - host: the hostname of the SMTP server
// - port: the port number to connect to on the SMTP server
// - timeout: the timeout for socket operations
Smtp::Smtp( const QString &user, const QString &pass, const QString &host, int port, int timeout )
{
     // Create a new QSslSocket instance to handle communication with the SMTP server
    socket = new QSslSocket(this);
    // Connect various signals from the socket to corresponding slots in this class

    connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()));
    connect(socket, SIGNAL(connected()), this, SLOT(connected() ) );
    connect(socket, SIGNAL(error(QAbstractSocket::SocketError)), this,SLOT(errorReceived(QAbstractSocket::SocketError)));
    connect(socket, SIGNAL(stateChanged(QAbstractSocket::SocketState)), this, SLOT(stateChanged(QAbstractSocket::SocketState)));
    connect(socket, SIGNAL(disconnected()), this,SLOT(disconnected()));


    // Set the username and password for SMTP authentication
    this->user = user;
    this->pass = pass;
     // Set the hostname and port number for the SMTP server

    this->host = host;
    this->port = port;
     // Set the timeout for socket operations
    this->timeout = timeout;


}

void Smtp::sendMail(const QString &from, const QString &to, const QString &subject, const QString &body, QStringList files)
{
     // Construct message header with To, From and Subject
    message = "To: " + to + "\n";
    message.append("From: " + from + "\n");
    message.append("Subject: " + subject + "\n");

    // Initialize MIME and add a boundary delimiter

    //Let's intitiate multipart MIME with cutting boundary "frontier"
    message.append("MIME-Version: 1.0\n");
    message.append("Content-Type: multipart/mixed; boundary=frontier\n\n");



    message.append( "--frontier\n" );
    // Set the content type of the message body to plain text
    //message.append( "Content-Type: text/html\n\n" );  //Uncomment this for HTML formating, coment the line below
    message.append( "Content-Type: text/plain\n\n" );
     // Add the email body
    message.append(body);
    message.append("\n\n");

    // Check if there are any files to be attached
    if(!files.isEmpty())
    {
          // Loop through each file path and attach the file to the email
        qDebug() << "Files to be sent: " << files.size();
        foreach(QString filePath, files)
        {
            QFile file(filePath);
            if(file.exists())
            {
                 // Open the file in read-only mode and check if it can be opened
                if (!file.open(QIODevice::ReadOnly))
                {
                    // Display an error message if the file could not be opened
                    qDebug("Couldn't open the file");
                    QMessageBox::warning( nullptr, tr( "Qt Simple SMTP client" ), tr( "Couldn't open the file\n\n" )  );
                        return ;
                }
                // Read the contents of the file into a QByteArray and encode it in base64
                QByteArray bytes = file.readAll();
                message.append( "--frontier\n" );
                // Set the content type of the file to application/octet-stream, which is used for binary files
                                // Set the content disposition to attachment and include the file name
                                // Set the content transfer encoding to base64 to encode the file contents
                message.append( "Content-Type: application/octet-stream\nContent-Disposition: attachment; filename="+ QFileInfo(file.fileName()).fileName() +";\nContent-Transfer-Encoding: base64\n\n" );
                message.append(bytes.toBase64());
                message.append("\n");
            }
        }
    }
    else
        qDebug() << "No attachments found";
      // Add a closing boundary delimiter to the message


    message.append( "--frontier--\n" );

    // Replace newlines with carriage return-line feed sequences as required by the SMTP protocol
    message.replace( QString::fromLatin1( "\n" ), QString::fromLatin1( "\r\n" ) );

    // Replace the terminating sequence with a double dot
    message.replace( QString::fromLatin1( "\r\n.\r\n" ),QString::fromLatin1( "\r\n..\r\n" ) );

     // Set the sender and recipient addresses and the state of the SMTP connection
    this->from = from;
    rcpt = to;
    state = Init;

    // Connect to the SMTP server at the specified address and port using TLS
    socket->connectToHostEncrypted("smtp.gmail.com",465); //"smtp.gmail.com" and 465 for gmail TLS

        // Wait for the connection to be established within the specified timeout period
    if (!socket->waitForConnected(timeout)) {
         qDebug()<< "send_mail " << socket->errorString();
     }

    t = new QTextStream( socket );



}

Smtp::~Smtp()
{
    delete t;
    delete socket;
}
// Slot function that is called when the socket state changes
void Smtp::stateChanged(QAbstractSocket::SocketState socketState)
{

    qDebug() <<"stateChanged " << socketState;
}

// Slot function that is called when an error is received from the socket
void Smtp::errorReceived(QAbstractSocket::SocketError socketError)
{
    qDebug() << "error " <<socketError;
}
// Slot function that is called when the socket is disconnected
void Smtp::disconnected()
{

    qDebug() <<"disconneted";
    qDebug() << "error "  << socket->errorString();
}
// Slot function that is called when the socket is connected
void Smtp::connected()
{
    qDebug() << "Connected ";
}
// Slot function that is called when data is available to be read from the socket
void Smtp::readyRead()
{

     qDebug() <<"readyRead";// output that data is ready to be read from the socket
    // SMTP is line-oriented

    QString responseLine;
    do
    {
        responseLine = socket->readLine();// read a line of data from the socket
        response += responseLine;// add the line of data to the response string
    }
    while ( socket->canReadLine() && responseLine[3] != ' ' );// continue reading until a line with a response code is received


    responseLine.truncate( 3 );// truncate the response line to the first three characters (the response code)

    qDebug() << "Server response code:" <<  responseLine;// output the response code
    qDebug() << "Server response: " << response;// output the full server response

    // Handle different states of the SMTP protocol
    if ( state == Init && responseLine == "220" )
    {
        // banner was okay, let's go on
        *t << "EHLO localhost" <<"\r\n";
        t->flush();

        state = HandShake;
    }
    //No need, because I'm using socket->startClienEncryption() which makes the SSL handshake for you
    else if (state == Tls && responseLine == "250")
    {
        // Trying AUTH
        qDebug() << "STarting Tls";
        *t << "STARTTLS" << "\r\n";// send the STARTTLS command to the server
        t->flush();
        state = HandShake;
    }
    else if (state == HandShake && responseLine == "250")
    {
        socket->startClientEncryption();// start client-side encryption on the socket
        if(!socket->waitForEncrypted(timeout))// wait for the encryption to complete
        {
            qDebug() << socket->errorString();
            state = Close;// move to the close state
        }


        //Send EHLO once again but now encrypted

        *t << "EHLO localhost" << "\r\n";
        t->flush();
        state = Auth;
    }
    else if (state == Auth && responseLine == "250")
    {
        // Trying to authenticate using AUTH protocol
        // Trying AUTH
        qDebug() << "Auth";
        *t << "AUTH LOGIN" << "\r\n";
        t->flush();
        // Move to User state to wait for server's response
        state = User;
    }
    else if (state == User && responseLine == "334")
    {
        // Trying to send the user's email address
        //Trying User
        qDebug() << "Username";
        //GMAIL is using XOAUTH2 protocol, which basically means that password and username has to be sent in base64 coding
        //https://developers.google.com/gmail/xoauth2_protocol
        *t << QByteArray().append(user).toBase64()  << "\r\n";
        t->flush();
         // Move to Pass state to wait for server's response
        state = Pass;
    }
    else if (state == Pass && responseLine == "334")
    {
         // Trying to send the user's password
        //Trying pass
        qDebug() << "Pass";
        *t << QByteArray().append(pass).toBase64() << "\r\n";
        t->flush();
        // Move to Mail state to wait for server's response

        state = Mail;
    }
    else if ( state == Mail && responseLine == "235" )
    {
        // HELO response was okay (well, it has to be)

        //Apperantly for Google it is mandatory to have MAIL FROM and RCPT email formated the following way -> <email@gmail.com>
        qDebug() << "MAIL FROM:<" << from << ">";
        *t << "MAIL FROM:<" << from << ">\r\n";
        t->flush();

        state = Rcpt;
    }
    else if ( state == Rcpt && responseLine == "250" )
    {
        //Apperantly for Google it is mandatory to have MAIL FROM and RCPT email formated the following way -> <email@gmail.com>
        *t << "RCPT TO:<" << rcpt << ">\r\n"; //r
        t->flush();
        state = Data;
    }
    else if ( state == Data && responseLine == "250" )
    {
         // Send DATA command to the server to indicate

        *t << "DATA\r\n";
        t->flush();
        state = Body;
    }
    else if ( state == Body && responseLine == "354" )
    {

        *t << message << "\r\n.\r\n";
        t->flush();
        state = Quit;
    }
    else if ( state == Quit && responseLine == "250" )
    {

        *t << "QUIT\r\n";
        t->flush();
        // here, we just close.
        //state = Close;
        emit status( tr( "Message sent" ) );
    }
    else if ( state == Close )
    {
          // If the state is Close, delete the object and return
        deleteLater();
        return;
    }
    else
    {
        // something broke.
     //   QMessageBox::warning( nullptr, tr( "Qt Simple SMTP client" ), tr( "Unexpected reply from SMTP server:\n\n" ) + response );
        state = Close;
        emit status( tr( "Failed to send message" ) );
    }
    response = "";
}
