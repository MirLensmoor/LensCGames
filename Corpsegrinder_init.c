program CorpsegrinderInitv2(char)

function gmsg (string msg)
{
  send_channel(msg, CHANNEL_GAMES);
}

main()
{
room lens = get_room_by_vnum(69001);
room ant = get_room_by_vnum(114003);
int i,time,iscore;
string imm = ch_getstring(self,CHAR_STRING_NAME);
argument = first_word(argument,WORD_REST);
int time = atoi(argument);
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
send_channel("Corpsegrinder has ended!",CHANNEL_GAMES);
invalidate extract_object(lbin);
invalidate extract_object(abin);
}