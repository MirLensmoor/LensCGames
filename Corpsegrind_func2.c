function DEBUG(string s)
{
  if(GV_DEBUG_ENABLE){
    send_channel(s, CHANNEL_WIZNET);
  }
}
function DEBUG(string s)
{
  if(GV_DEBUG_ENABLE){
    send_channel(s, CHANNEL_WIZNET);
  }
}
function bail (char who, string why) {
    sendt(who, why + "\r\n");
    end;
}

function string snip (string input) {
    return string_prefix(input, string_length(input) - 2);
}

function qmsg (string msg)
{
  send_channel(msg, CHANNEL_QUEST);
}

function game_set_memory_string(int vnum, string msg)
{
  int data = game_get_memory_value(vnum);
  game_set_memory(vnum, data, msg);
}
function game_set_memory_value(int vnum, int data)
{
  string msg = game_get_memory_string(vnum);
  game_set_memory(vnum, data, msg);
}
function int GetPoint(int DATA_VNUM, string name)
{
  DEBUG("Entry, GetPoint");
  // DATA FORMAT: <name> <points>
  string Read = game_get_memory_string(DATA_VNUM);
  string Write= "";
  string Line = "";
  string LineNoChange= ""; /* Stores the line in case it didnt change */
  while (!string_is_empty(Read))
  {
    /* Get the first line from the desc */
    Line = first_word(Read, WORD_FIRST);
    /* Update the Read var to shave off the line we parse*/
    Read = first_word(Read, WORD_REST);
    
    /* Fetch the name */
    string LineUser = first_word(Line,WORD_FIRST);
    Line = first_word(Line,WORD_REST);
    if (LineUser == name)
    {
      return atoi(Line);
    }
  }
  return -1;
}
function int AddPoint(int DATA_VNUM, string name)
{
  DEBUG("Entry, AddPoint");
  // DATA FORMAT: <name> <points>
  string Read = game_get_memory_string(DATA_VNUM);
  string Write= "";
  string Line = "";
  string LineNoChange= ""; /* Stores the line in case it didnt change */
  int QuestPointCount = GetPoint(DATA_VNUM, name);
  DEBUG("AddPointQPC[" + QuestPointCount + "]");
  if(QuestPointCount == -1)
  {
    Write = Read + "'" + name + " 1'";
    DEBUG("Not found, adding line ['" + name + " 1']");
  }
  else
  {
    bool found=FALSE;
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
      if (LineUser == name)
      {
        Line = "" + LineUser + " " + (QuestPointCount+1);
        DEBUG("Found, Changing line [" + Line + "] from existing [" + LineNoChange + "]");
      }
      else
      {
        Line = LineNoChange;
      }
      Write += "'" + Line + "'\n";
    }
  }
  DEBUG("Setting Game Memory.");
  game_set_memory(DATA_VNUM, 1, Write);
}
