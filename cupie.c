program cupie(obj)
main()
{
 obj egg = self;
 char ch = obj_carried_by(egg);
 int i = 1;
 int itmp;
 int count = 0;
  
 if (!is_valid_char(ch))
 { end; }
 string cname = ch_getstring(ch,CHAR_STRING_NAME);
  while (is_valid_obj(egg))
  {
   itmp = random(2,((ch_getval(ch,CHAR_VAL_LEVEL)/5)));
   quest_award(ch,itmp);
   i += itmp;
   count ++;
   invalidate extract_object(egg);
   egg = get_obj_carry(ch,"@cupie");
  }
 
  if (ch_getval(ch,CHAR_VAL_LEVEL) > 91)
  {
  i = count * 10;
  reward_player(ch, REWARD_QPS, i);  
  }
  sendt(ch,"You receive "+itmp+" quest points from your eggs!\r\n");
  send_channel(""+cname+" got "+itmp+" quest points in "+count+" cupie eggs!",CHANNEL_GAMES);
}