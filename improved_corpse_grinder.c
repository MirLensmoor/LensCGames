program improved_corpse_grinder(char)
 
#include 146008
#include 271001
#include 271002
#include 271014 /*zombie plushies */
 main()
 {
  char ch = self;
  obj cg = get_obj_room(ch,"@cg");
  string chname = ch_getstring(ch,CHAR_STRING_NAME);
  obj corpse = get_obj_carry(ch,"corpse");
 
  if (!is_valid_obj(corpse))
   { 
    sendt(ch,"Unless you plan on throwing youself in, "
    +"you have no corpse.\r\n");
    end;
   }
 
  int last = obj_getval(corpse,OBJ_VAL_LOWNER);
  int curr = ch_getval(ch,CHAR_VAL_ID);
 
  if (last != curr)
   {
    sendt(ch,"Getting someone else to kill for you?"
    +" Shame on you! No prize!\r\n");
     end;
   }
 
 
  if (obj_getval(corpse,OBJ_VAL_VNUM) != 10)
   {
    sendt(ch,"Nice try, but that's not a real corpse.\r\n");
    string cheat = ""+chname+" tried to use a fake corpse.";
    send_note("imm","CorpseGrinder","cheater",cheat,NOTE_NOTE);
    end;
   }
 
  int plev = ch_getval(ch,CHAR_VAL_LEVEL);
  int clev = obj_getval(corpse,OBJ_VAL_LEVEL);
 
   if (clev < (plev -(plev + 10) / 10 ))
    {
     sendt(ch,"You expect a prize for this wimpy kill?!"
     +"I don't think so, you pansy!\r\n");
     end;
    }
 
  int x = random(0,100);
  
if (x < 1)
{
 int i = random(0,100);
if (i <= 50)
 {
  i= random(0,100);
   if (i >= 75)
    {
        make_token(ch,cg);
       }
     }
    else make_cupie(ch,cg);
   }
   if (x > 0 && x <= 45)
  {
   make_cupie(ch,cg); }
 
   if (x > 45 && x <= 60)
  {
   make_coins(ch,cg); }
 
   if (x > 60 && x <= 70)
   {
    if (random(0,15) < ((plev + 10)/10)) 
     {    
      make_plushie(ch,cg); 
     }
     else make_cupie(ch,cg);
   }
 
   if (x > 70)
  {
   make_pcoin(ch,cg);
   }
 
 invalidate extract_object(corpse);
 }
 
