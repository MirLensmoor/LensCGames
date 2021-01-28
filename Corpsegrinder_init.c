program CorpsegrinderInitv2(char)

#include 271004

main()
{
room lens = get_room_by_vnum(69001);
room ant = get_room_by_vnum(114003);
int i,time,iscore;
string imm = ch_getstring(self,CHAR_STRING_NAME);
argument = first_word(argument,WORD_REST);
int time = atoi(argument);
int GLOBAL_DATA_VNUM = 271017;
 if (string_is_empty(argument))
  {
   sendt(self,"Please supply a duration time in minutes.\r\n");
   sendt(self,"grindstart (duration in minutes)\r\n");
   end;
  }
gmsg("Corpsegrinder v2 has been started by "+imm+".");
gmsg("Corpsegrinder will last "+time+" minutes.");
gmsg("You are allowed to Grind Corpses while on a Quest.");
gmsg("Corpsegrinders are located in Lensmoor and Semdea morgues.");

obj lbin = create_obj(271017,lens);
obj abin = create_obj(271017,ant);
while(time>=0)
 {
   pause(60);
   if(time % 5 == 0 || time <= 5)
   {
     if(time == 1)
     {
       gmsg("There is 1 minute left on Corpsegrinder!");
       send_channel("LensC quest running, 1 minute left.", CHANNEL_WIZNET);
     }
     else if(time == 0)
     {
       send_channel("LensC quest completed.", CHANNEL_WIZNET);
     }
     else
     {
       gmsg("There are " + time + " minutes left on Corpsegrinder!");
       send_channel("LensC quest running, "+time+" minutes left.", CHANNEL_WIZNET);
     }
   }
   time--;
 }
  //disable scoring of points
  else
  {
	game_set_memory_value(GLOBAL_DATA_VNUM, 0);
    qmsg("The quest has ended!");
  }
  
  //Print scoreboard
  qmsg("---- Scoreboard ----");
  
  int scorelist[64];
  string namelist[64];
  string Read = game_get_memory_string(GLOBAL_DATA_VNUM);
  string Line = "";
  
  int iter = 0;
  
  while (!string_is_empty(Read))
  {
    /* Get the first line from the desc */
    Line = first_word(Read, WORD_FIRST);
    /* Update the Read var to shave off the line we parse*/
    Read = first_word(Read, WORD_REST);
    
    /* Fetch the name */
    string LineUser = first_word(Line,WORD_FIRST);
    Line = first_word(Line,WORD_REST);
    namelist[iter]  = LineUser;
    scorelist[iter] = atoi(Line);
    iter++;
  }
  

  DEBUG("Sorting...\n\r");
  
  string tempname;
  int tempscore;
  int i, j, temp;
  
  for (i = 0; i < (iter - 1); ++i)
  {
    for (j = 0; j < iter - 1 - i; ++j )
    {
      if (scorelist[j] < scorelist[j+1])
      {
        tempscore = scorelist[j+1];
        scorelist[j+1] = scorelist[j];
        scorelist[j] = tempscore;
        
        tempname = namelist[j+1];
        namelist[j+1] = namelist[j];
        namelist[j] = tempname;
      }
    }
  }
  DEBUG("Sorting done.");
  
  DEBUG("Printing list.");
  int total = 0;
  for(i=0;i<iter;i++)
  {
    qmsg(fpad(namelist[i],14) + "   " + pad(scorelist[i],3));
    total += scorelist[i];
  }
  qmsg("--------------------");
  qmsg(fpad("Total",14) + "   " + pad(total,3));
  game_clear_memory(GLOBAL_DATA_VNUM); /* No need to store the scoreboard */
  interpret(score_mob, "mobact extract");
  send_channel("Corpsegrinder has ended!",CHANNEL_GAMES);
  invalidate extract_object(lbin);
  invalidate extract_object(abin);
}