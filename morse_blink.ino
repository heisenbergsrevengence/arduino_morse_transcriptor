# include <string.h>
const byte numChars = 32;
char receivedChars[numChars];
bool newData=false;
char temp;
char morse_dict[26+10][6]= { ".-",   "-...", "-.-.", "-..",  ".",    "..-.",
            "--.",  "....", "..",   ".---", "-.-",  ".-..",
            "--",   "-.",   "---",  ".--.", "--.-", ".-.",
            "...",  "-",    "..-",  "...-", ".--",  "-..-",
            "-.--", "--..",".----","..---","...--","....--",".....","-....","--...","---..","----.","-----"};
char* output_str;
char english_dict[26+10] = {
    'a','b','c','d','e','f','g','h','i','j','k','l','m',
    'n','o','p','q','r','s','t','u','v','w','x','y','z',
    '1','2','3','4','5','6','7','8','9','0'
};
void setup() {
  pinMode(2,OUTPUT);
  pinMode(13,OUTPUT);
  Serial.begin(9600);
  Serial.println("enter string to turn into morse: ");
}
void morse_output(char input_str[]){
  for (int i=0; input_str[i]!='\0';i++){
    char c = input_str[i];
    if (c==' '){ digitalWrite(13,HIGH);
    delay(100);}

    for (int j=0;j<26+10;j++){
      if(c == english_dict[j]){
        for (int k=0;morse_dict[j][k]!='\0';k++){
          if(morse_dict[j][k]=='.'){
            digitalWrite(2,HIGH);
            delay(500);
          }
          else{
            digitalWrite(2,HIGH);
            delay(1000);
          }
          digitalWrite(2,LOW);
          digitalWrite(13,LOW);
          delay(500);
          //output_str = strcat(morse_dict[j][k],output_str);}
   }
  }
 }
}
Serial.println("morse transcript finished.enter new string to encode: ");
}
void loop() {
    recvWithEndMarker();
    showNewData();
}

void recvWithEndMarker() {
    static byte ndx = 0;
    char endMarker = '\n';
    char rc;
    
    while (Serial.available() > 0 && newData == false) {
        rc = Serial.read();

        if (rc != endMarker) {
            receivedChars[ndx] = rc;
            ndx++;
            if (ndx >= numChars) {
                ndx = numChars - 1;
            }
        }
        else {
            receivedChars[ndx] = '\0'; // terminate the string
            ndx = 0;
            newData = true;
        }
    }
}

void showNewData() {
    if (newData == true) {
        Serial.println("morseing");
        morse_output(receivedChars);
        newData = false;
    }
}