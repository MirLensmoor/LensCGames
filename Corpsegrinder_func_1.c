function up_scores(obj cg, string field, int val)
{
 string temp = obj_getextra(cg,field);
 int pval = atoi(temp);
 val = (val + pval);
 obj_setextra(cg,field,""+val,TRUE);
}

function make_token( char ch, obj cg)
{
 if (!is_valid_char(ch)) { end; }
 room rm = ch_in_room(ch);
 obj token = create_obj(271004,rm);
 move_obj_to_char(token,ch);
 sendt(ch,"CONGRATULATIONS! You get a corpse token!\r\n");
 string name = ch_getstring(ch,CHAR_STRING_NAME);
 send_channel(name + " recieved a corpse IMM token from the Corpse
Grinder!"
,CHANNEL_QUEST);
 up_scores(cg,"@tokens",1);
}

function make_cupie( char ch, obj cg)
{
 if (!is_valid_char(ch)) { end; }
 room rm = ch_in_room(ch);
 obj cupie = create_obj(271002,rm);
 move_obj_to_char(cupie,ch);
 sendt(ch,"CONGRATULATIONS! You get a cupie egg!\r\n");
 string name = ch_getstring(ch,CHAR_STRING_NAME);
 up_scores(cg,"@cupies",1);
}

function make_cupiev2( char ch, obj cg)
{
 if (!is_valid_char(ch)) { end; }
 room rm = ch_in_room(ch);
 obj cupie = create_obj(271016,rm);
 move_obj_to_char(cupie,ch);
 sendt(ch,"CONGRATULATIONS! You get a cupie egg!\r\n");
 string name = ch_getstring(ch,CHAR_STRING_NAME);
 up_scores(cg,"@cupies",1);
}


function make_coins(char ch, obj cg)
{
 if (!is_valid_char(ch)) { end; }
 int plev = ch_getval(ch,CHAR_VAL_LEVEL);
 room rm = ch_in_room(ch);
 int i = random(1,(plev + 10)/10);
 add_cash(ch,0,0,i);
 sendt(ch,"CONGRATULATIONS! You win "+i+" platinum!\r\n");
 string name = ch_getstring(ch,CHAR_STRING_NAME);
 up_scores(cg,"@coins",i);
}

function make_pcoin(char ch, obj cg)
 {
 if (!is_valid_char(ch)) { end; }
 room rm = ch_in_room(ch);
 int i = random(1,10);
 int temp = i;
 for (i;i>0;i--)
  {
   obj pcoin = create_obj(271008,rm);
   move_obj_to_char(pcoin,ch);
  }

 sendt(ch,"CONGRATULATIONS! You win "+temp+" plushie coins!\r\n");
 string name = ch_getstring(ch,CHAR_STRING_NAME);
 up_scores(cg,"@pcoins",i);
 }