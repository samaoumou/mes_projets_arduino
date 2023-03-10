/************************************************************************
   Envoi d'un email par l'ESP32
   
   Utilise la bibliothèque ESP Mail Client par Mobizt:
   https://github.com/mobizt/ESP-Mail-Client
   Pour plus d'informations:
   https://electroniqueamateur.blogspot.com/2021/01/envoi-dun-email-par-lesp32.html
   
 *************************************************************************/

#include <WiFi.h>
#include <ESP_Mail_Client.h>

// identfication du réseau wifi local
#define WIFI_SSID "Issa"
#define WIFI_PASSWORD "0501Issa"

// identification du compte email utilisé pour l'envoi
#define SMTP_HOST "smtp.gmail.com"
#define SMTP_PORT 587 //assurez vous d'utiliser le bon numéro de port
#define AUTHOR_EMAIL "astouissa4@gmail.com"
#define AUTHOR_PASSWORD "0501Iss@ndiaye"

// identification du destinataire
#define RECIPIENT_NAME "Issa Ndiaye"
#define RECIPIENT_EMAIL "ndiayeissa598@gmail.com"

#define EMAIL_TITLE "Temp"

SMTPSession smtp;

void setup()
{
  // connexion au réseau Wifi et affichage dans le moniteur série
  Serial.begin(115200);
  Serial.println();

  Serial.print("Connexion au reseau Wifi.");

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(200);
  }

  Serial.println("reussie");
  Serial.println();

  smtp.callback(smtpCallback); // permettra de suivre le déroulement sur le moniteur série

  send_email(); // routine qui envoie le email

}

void loop()
{
  // dans cet exemple, le email est envoyé une seule fois, au démarrage du programme
}

void send_email()
{
  ESP_Mail_Session session;
  char contenu_message[100]; // ici ajusté à 100 caractères maximum
  SMTP_Message message;

  session.server.host_name = SMTP_HOST;
  session.server.port = SMTP_PORT;
  session.login.email = AUTHOR_EMAIL;
  session.login.password = AUTHOR_PASSWORD;

  message.sender.name = "ESP32";
  message.sender.email = AUTHOR_EMAIL;
  message.subject = EMAIL_TITLE;
  message.addRecipient(RECIPIENT_NAME, RECIPIENT_EMAIL);

  // construction du corps du message (inclusion d'un nombre aléatoire)
  sprintf(contenu_message, "Temperature mesuree: %.2f °C", random(10000)/100.0);
  message.text.content = contenu_message;
  
  message.priority = esp_mail_smtp_priority::esp_mail_smtp_priority_normal;

  if (!smtp.connect(&session))   // connexion au serveur SMTP
    return;

  if (!MailClient.sendMail(&smtp, &message))   // envoi du email
    Serial.println("Erreur lors de l'envoi du email, " + smtp.errorReason());
}

// Affichage d'infos dans le moniteur série pendant l'envoi du email
void smtpCallback(SMTP_Status status)
{
  Serial.println(status.info());
}
