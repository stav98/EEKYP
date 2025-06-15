void init_commands(void);
void printErr1(void);
void printErr2(void);
void soft_reset(int, char**);
void print_version(int, char**);
void help(int, char**);
void set_out(int, char**);

const char PROGMEM 
   //        1         |           2         |         3            |         4            |          5          |
   
   //ct16[] = "getlora"  , ct17[] = "eeclear"  , ct18[] = "verb"      , ct19[] = "save"      , ct20[] = "rst"      ,
     ct01[] = "setout"   , ct02[] = "rst"      , ct03[] = "version"  , ct04[] = "?";

//Δομή συνδεδεμένης λίστας
const L_cmd PROGMEM cmd04 = {(char*) ct04   , help,             NULL}; //? Παρουσίασε εντολές
const L_cmd PROGMEM cmd03 = {(char*) ct03   , print_version,  &cmd04}; //Έκδοση λογισμικού
const L_cmd PROGMEM cmd02 = {(char*) ct02   , soft_reset,     &cmd03}; //Κάνει reset
const L_cmd PROGMEM cmd01 = {(char*) ct01   , set_out,     &cmd02}; //Βγάζει έξοδο σε pin


void init_commands(void)
{
 cmd_tbl = (L_cmd*) &cmd01;
}

void printErr1()
{
 Serial.println(F("Too few arguments"));
}

void printErr2()
{
 Serial.println(F("Syntax error"));
}

void soft_reset(int arg_cnt, char **args)
{
 resetFunc();
}

void print_version(int arg_cnt, char **args)
{
 Serial.print(F("Version: "));
 Serial.println(VERSION);
}

void set_out(int arg_cnt, char **args)
{
 if (arg_cnt > 2)
    {
     if (strcmp_P(args[1], PSTR("SW1")) == 0)
        {
         if (strcmp_P(args[2], PSTR("ON")) == 0)    
            { 
             VALVE1_ON(); 
            }
         else if (strcmp_P(args[2], PSTR("OFF")) == 0)
            {
             VALVE1_OFF();
            }
        }
     else if (strcmp_P(args[1], PSTR("SW2")) == 0)
        {
         if (strcmp_P(args[2], PSTR("ON")) == 0)    
            { 
             VALVE2_ON(); 
            }
         else if (strcmp_P(args[2], PSTR("OFF")) == 0)
            {
             VALVE2_OFF();
            }
        }
     else 
         printErr2(); //Syntax error
    }
 else
     printErr1();
}

void help(int arg_cnt, char **args)
{
 char buf[10];
 L_cmd *cmd_entry;
 for (cmd_entry = cmd_tbl; cmd_entry != NULL; cmd_entry = (L_cmd*)pgm_read_word(&cmd_entry->next))
     {
      strcpy_P(buf, (char*)pgm_read_word(&cmd_entry->cmd));
      Serial.println(buf);
     }
}