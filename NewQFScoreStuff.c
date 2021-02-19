program RegisterForQuestfest(obj)

int PROGRAM_VNUM=453000;
int QF_QP_ENTRY_STORE = 365027;
int QF_QP_FINISH_STORE = 365028;
int QF_START_EPOCH = 1315598482 ;
int QF_END_EPOCH = 0;
int QF_START_EPOCH_VNUM = 365026;

int MEM_START_EPOCH = 0; /* Not a constant */

bool QF_ALLOW_REREGISTER = FALSE;

char ch; /* Global because we're lazy */


function int StoreQP(int DATA_VNUM, char ch_registrant){

    // DATA FORMAT: <name> <qp> <timestamp> <score>
    string Read = game_get_memory_string(DATA_VNUM);
    string Write= "";
    string Line = "";
    string LineNoChange= ""; /* Stores the line in case it didnt change */
    string NewUser = ""; /* character name from argument */
	string strQP = "";
	string oldScore = "";
    int QuestPointCount = -1;
	int Score = 0;
    
    if(!is_valid_char(ch_registrant))
    {
      LOGWIZ("Invalid char in QuestFestRegister");
      end;
    }
    NewUser = ch_getstring(ch_registrant, CHAR_STRING_NAME); 
    QuestPointCount = ch_getval(ch_registrant, CHAR_VAL_QUEST_POINTS);
    
    bool re_register=FALSE;
    while (!string_is_empty(Read))
    {
		
	  
      /* Get the first line from the desc */
      Line = first_word(Read, WORD_FIRST);
      /* Save the line in case we dont want to change it */
      LineNoChange= Line;
      /* Update the Read var to shave off the line we parse*/
      Read = first_word(Read, WORD_REST);
      
      /* Fetch the name */
      string LineUser = first_word(Line,WORD_FIRST);
      Line = first_word(Line,WORD_REST);
	  strQP = first_word(Line,WORD_FIRST);
	  Line = first_word(Line,WORD_REST);
	  oldScore = first_word(Line,WORD_REST);
	  LOGWIZ("Line Value #1 [" + Line + "]"); 
	  
      if (LineUser == NewUser)
      {
		LOGWIZ("Line 60");
		Score = QuestPointCount - atoi(strQP) + atoi(oldScore);
        re_register = TRUE;
        Line = "" + LineUser + " " + QuestPointCount + " " + get_systime() + " " + Score;
      }else{
        Line = LineNoChange;
      }
      Write += "'" + Line + "'\n";
    }
    
    if (!re_register)
    {
	 LOGWIZ("Line 71");
      Write += "'" + NewUser 
            +  " " + QuestPointCount 
            + " " + get_systime() 
			+ " " + Score
            + "'\n";
    }
    if(!re_register 
   || (re_register && QF_ALLOW_REREGISTER)
   || DATA_VNUM == QF_QP_FINISH_STORE){
	  LOGWIZ("Line 81");
      game_set_memory(DATA_VNUM, 1, Write);
      return QuestPointCount;
    }
    return -1;
}
function string GetTime()
{
  int t = get_systime();

  t = t-MEM_START_EPOCH;
  
  t=abs(t);
  
  int d = t/86400;
  t-=d*86400;

  int h = t/3600;
  t-=h*3600;

  int m = t/60;
  t-=m*60;

  int s = t;
  
  string a = "";
  if(d>0)
  {
    a += "" + d + " days, ";
  }
  if(d>0 || h>0)
  {
    a += "" + h + " hours, ";
  }
  a += "" + m + " minutes and ";
  a += "" + s + " seconds.";
  return a;
}
function string GetHelp()
{
  string sh = "";
  sh += "[QuestFest Registry]\r\n";
  sh += "questfest register - Register your starting QP\r\n";
  sh += "questfest finish - Register your finish QP\r\n";
  return sh;
}

function MSG(string s)
{
  act(s, ch, NULLOBJ, NULLCHAR,ACT_TO_CHAR);
}

function LOGWIZ(string text)
{
  string outt = "LOGGER [" + PROGRAM_VNUM + "]: ";
  send_channel(outt + text,CHANNEL_WIZNET);
}

main()
{
  
  MEM_START_EPOCH = game_get_memory_value(QF_START_EPOCH_VNUM);
  if(MEM_START_EPOCH < 1300000000){
    LOGWIZ("Missing or invalid start epoch for QP Register obelisk!");
  }
  
  string ArgUser = first_word(argument, WORD_FIRST);
  argument = first_word(argument,WORD_REST);
  argument = first_word(argument,WORD_REST); // strip away 'questfest'
  string cmd = first_word(argument,WORD_FIRST);
  argument = first_word(argument,WORD_REST);
  
  room here = obj_in_room(self);
  ch = get_char_in_room(here, ArgUser);
  
  if(!is_valid_char(ch)){
    LOGWIZ("Bork in QFS [" + ArgUser + "]");
    end;
  }
  
  if(  get_systime() < MEM_START_EPOCH 
    && string_prefix(cmd,4) != "test"
   && cmd != "setstart"
   )
  {
    sendt(ch, "QuestFest will be starting in " + GetTime() + "\r\n");
    end;
  }
  switch(cmd)
  {
    case "testregister":
    case "register":
      int qp = StoreQP(QF_QP_ENTRY_STORE, ch);
      string ss = "";
      string wn = "";
      if(qp>=0){
      ss = "Your QP have been recorded as [" + qp + "]";
      wn = "QuestFest Register [" + ch.name + "] with [" 
                + qp + "] QP at time [" + get_systime() + "]";
      }
      else
      {
      ss = "You have already registered!";
      wn = "QuestFest Re-register attempt by [" + ch.name + "] at time ["
         + get_systime() + "]";
      }
      sendt(ch,ss + "\r\n");
      LOGWIZ(wn);
    break;
    //case "testfinish":
    case "finish":
      int qp = StoreQP(QF_QP_FINISH_STORE, ch);
      string ss = "Your QP have been recorded as [" + qp + "]";
      sendt(ch,ss + "\r\n");
      LOGWIZ("QuestFest Finish [" + ch.name + "] with ["
            + qp + "] QP at time [" + get_systime() + "]");
    break;
    case "setstart":
      if(ch.LEVEL < 92)
      {
        MSG("You are not an immortal now are you...");
        LOGWIZ("Character [" + ch.name + "] tried setting QP-Obelisk"
        + " start time using 'settime' command!");
        end;
      }
      else
      {
       int input_timestamp = atoi(argument);
        if(input_timestamp == 0)
        {
          MSG("Supply a unix epoch timestamp.");
          end;
        }
        else
        {
          if(input_timestamp < get_systime())
          {
            MSG("Silly goose! That timestamp is in the past.");
            end;
          }
          MSG("Setting timestamp to [" + input_timestamp + "]");
          game_set_memory(QF_START_EPOCH_VNUM, input_timestamp, "Start Epoch for QP obelisk");
        }
      }
   break;
    default:
      sendt(ch, GetHelp());
    break;
  }
}