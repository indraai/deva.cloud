/**************************************************************************
*  File: oedit.c                                           Part of tbaMUD *
*  Usage: Oasis OLC - Objects.                                            *
*                                                                         *
* By Levork. Copyright 1996 Harvey Gilpin. 1997-2001 George Greer.        *
**************************************************************************/

#include "conf.h"
#include "sysdep.h"
#include "structs.h"
#include "utils.h"
#include "comm.h"
#include "interpreter.h"
#include "spells.h"
#include "db.h"
#include "boards.h"
#include "constants.h"
#include "shop.h"
#include "genolc.h"
#include "genobj.h"
#include "genzon.h"
#include "oasis.h"
#include "improved-edit.h"
#include "dg_olc.h"
#include "fight.h"
#include "modify.h"

/* local functions */
static void oedit_setup_new(struct descriptor_data *d);
static void oedit_disp_container_flags_menu(struct descriptor_data *d);
static void oedit_disp_extradesc_menu(struct descriptor_data *d);
static void oedit_disp_prompt_apply_menu(struct descriptor_data *d);
static void oedit_liquid_type(struct descriptor_data *d);
static void oedit_disp_apply_menu(struct descriptor_data *d);
static void oedit_disp_weapon_menu(struct descriptor_data *d);
static void oedit_disp_spells_menu(struct descriptor_data *d);
static void oedit_disp_val1_menu(struct descriptor_data *d);
static void oedit_disp_val2_menu(struct descriptor_data *d);
static void oedit_disp_val3_menu(struct descriptor_data *d);
static void oedit_disp_val4_menu(struct descriptor_data *d);
static void oedit_disp_type_menu(struct descriptor_data *d);
static void oedit_disp_extra_menu(struct descriptor_data *d);
static void oedit_disp_wear_menu(struct descriptor_data *d);
static void oedit_disp_menu(struct descriptor_data *d);
static void oedit_disp_perm_menu(struct descriptor_data *d);
static void oedit_save_to_disk(int zone_num);

/* handy macro */
#define S_PRODUCT(s, i) ((s)->producing[(i)])

/* Utility and exported functions */
ACMD(do_oasis_oedit)
{
  int number = NOWHERE, save = 0, real_num;
  struct descriptor_data *d;
  char buf1[MAX_STRING_LENGTH];
  char buf2[MAX_STRING_LENGTH];

  /* No building as a mob or while being forced. */
  if (IS_NPC(ch) || !ch->desc || STATE(ch->desc) != CON_PLAYING)
    return;

  /* Parse any arguments. */
  two_arguments(argument, buf1, buf2);

  /* If there aren't any arguments they can't modify anything. */
  if (!*buf1) {
    send_to_char(ch, "\ninfo:Specify an object VNUM to edit.\r");
    return;
  } else if (!isdigit(*buf1)) {
    if (str_cmp("save", buf1) != 0) {
      send_to_char(ch, "\nerror:Yikes! Stop that, someone will get hurt!\r");
      return;
    }

    save = TRUE;

    if (is_number(buf2))
      number = atoi(buf2);
    else if (GET_OLC_ZONE(ch) > 0) {
      zone_rnum zlok;

      if ((zlok = real_zone(GET_OLC_ZONE(ch))) == NOWHERE)
        number = NOWHERE;
      else
        number = genolc_zone_bottom(zlok);
    }

    if (number == NOWHERE) {
      send_to_char(ch, "\nSave which zone?\r");
      return;
    }
  }

  /* If a numeric argument was given, get it. */
  if (number == NOWHERE)
    number = atoi(buf1);

  if (number < IDXTYPE_MIN || number > IDXTYPE_MAX) {
    send_to_char(ch, "\ninfo:That object VNUM can't exist.\r");
    return;
  }

  /* Check that whatever it is isn't already being edited. */
  for (d = descriptor_list; d; d = d->next) {
    if (STATE(d) == CON_OEDIT) {
      if (d->olc && OLC_NUM(d) == number) {
        send_to_char(ch, "\ninfo:That object is currently being edited by %s.\r",
          PERS(d->character, ch));
        return;
      }
    }
  }

  /* Point d to the builder's descriptor (for easier typing later). */
  d = ch->desc;

  /* Give the descriptor an OLC structure. */
  if (d->olc) {
    mudlog(BRF, LVL_IMMORT, TRUE,
      "SYSERR: do_oasis: Player already had olc structure.");
    free(d->olc);
  }

  CREATE(d->olc, struct oasis_olc_data, 1);

  /* Find the zone. */
  OLC_ZNUM(d) = save ? real_zone(number) : real_zone_by_thing(number);
  if (OLC_ZNUM(d) == NOWHERE) {
    send_to_char(ch, "\ninfo:Sorry, there is no zone for that number!\r");

    /* Free the descriptor's OLC structure. */
    free(d->olc);
    d->olc = NULL;
    return;
  }

  /* Everyone but IMPLs can only edit zones they have been assigned. */
  if (!can_edit_zone(ch, OLC_ZNUM(d))) {
    send_cannot_edit(ch, zone_table[OLC_ZNUM(d)].number);
    /* Free the OLC structure. */
    free(d->olc);
    d->olc = NULL;
    return;
  }

  /* If we need to save, save the objects. */
  if (save) {
    send_to_char(ch, "\nsave:Saving all objects in zone %d.\r",
      zone_table[OLC_ZNUM(d)].number);
    mudlog(CMP, MAX(LVL_BUILDER, GET_INVIS_LEV(ch)), TRUE,
      "OLC: %s saves object info for zone %d.", GET_NAME(ch),
      zone_table[OLC_ZNUM(d)].number);

    /* Save the objects in this zone. */
    save_objects(OLC_ZNUM(d));

    /* Free the descriptor's OLC structure. */
    free(d->olc);
    d->olc = NULL;
    return;
  }

  OLC_NUM(d) = number;

  /* If a new object, setup new, otherwise setup the existing object. */
  if ((real_num = real_object(number)) != NOTHING)
    oedit_setup_existing(d, real_num);
  else
    oedit_setup_new(d);

  oedit_disp_menu(d);
  STATE(d) = CON_OEDIT;

  /* Send the OLC message to the players in the same room as the builder. */
  act("$n starts using OLC.", TRUE, d->character, 0, 0, TO_ROOM);
  SET_BIT_AR(PLR_FLAGS(ch), PLR_WRITING);

  /* Log the OLC message. */
  mudlog(CMP, MAX(LVL_IMMORT, GET_INVIS_LEV(ch)), TRUE, "OLC: %s starts editing zone %d allowed zone %d",
    GET_NAME(ch), zone_table[OLC_ZNUM(d)].number, GET_OLC_ZONE(ch));
}

static void oedit_setup_new(struct descriptor_data *d)
{
  CREATE(OLC_OBJ(d), struct obj_data, 1);
  clear_object(OLC_OBJ(d));
  OLC_OBJ(d)->name = strdup("[keywords]");
  OLC_OBJ(d)->short_description = strdup("[name]");
  OLC_OBJ(d)->description = strdup(":id:/main:avatar");
  OLC_OBJ(d)->action_description = strdup(":id:/main:look");
  SET_BIT_AR(GET_OBJ_WEAR(OLC_OBJ(d)), ITEM_WEAR_TAKE);
  OLC_VAL(d) = 0;
  OLC_ITEM_TYPE(d) = OBJ_TRIGGER;

  SCRIPT(OLC_OBJ(d)) = NULL;
  OLC_OBJ(d)->proto_script = OLC_SCRIPT(d) = NULL;
}

void oedit_setup_existing(struct descriptor_data *d, int real_num)
{
  struct obj_data *obj;

  /* Allocate object in memory. */
  CREATE(obj, struct obj_data, 1);
  copy_object(obj, &obj_proto[real_num]);

  /* Attach new object to player's descriptor. */
  OLC_OBJ(d) = obj;
  OLC_VAL(d) = 0;
  OLC_ITEM_TYPE(d) = OBJ_TRIGGER;
  dg_olc_script_copy(d);
  /* The edited obj must not have a script. It will be assigned to the updated
   * obj later, after editing. */
  SCRIPT(obj) = NULL;
  OLC_OBJ(d)->proto_script = NULL;
}

void oedit_save_internally(struct descriptor_data *d)
{
  int i;
  obj_rnum robj_num;
  struct descriptor_data *dsc;
  struct obj_data *obj;

  i = (real_object(OLC_NUM(d)) == NOTHING);

  if ((robj_num = add_object(OLC_OBJ(d), OLC_NUM(d))) == NOTHING) {
    log("oedit_save_internally: add_object failed.");
    return;
  }

  /* Update triggers and free old proto list  */
  if (obj_proto[robj_num].proto_script &&
      obj_proto[robj_num].proto_script != OLC_SCRIPT(d))
    free_proto_script(&obj_proto[robj_num], OBJ_TRIGGER);
  /* this will handle new instances of the object: */
  obj_proto[robj_num].proto_script = OLC_SCRIPT(d);

  /* this takes care of the objects currently in-game */
  for (obj = object_list; obj; obj = obj->next) {
    if (obj->item_number != robj_num)
      continue;
    /* remove any old scripts */
    if (SCRIPT(obj))
      extract_script(obj, OBJ_TRIGGER);

    free_proto_script(obj, OBJ_TRIGGER);
    copy_proto_script(&obj_proto[robj_num], obj, OBJ_TRIGGER);
    assign_triggers(obj, OBJ_TRIGGER);
  }
  /* end trigger update */

  if (!i)	/* If it's not a new object, don't renumber. */
    return;

  /* Renumber produce in shops being edited. */
  for (dsc = descriptor_list; dsc; dsc = dsc->next)
    if (STATE(dsc) == CON_SEDIT)
      for (i = 0; S_PRODUCT(OLC_SHOP(dsc), i) != NOTHING; i++)
	if (S_PRODUCT(OLC_SHOP(dsc), i) >= robj_num)
	  S_PRODUCT(OLC_SHOP(dsc), i)++;


  /* Update other people in zedit too. From: C.Raehl 4/27/99 */
  for (dsc = descriptor_list; dsc; dsc = dsc->next)
    if (STATE(dsc) == CON_ZEDIT)
      for (i = 0; OLC_ZONE(dsc)->cmd[i].command != 'S'; i++)
        switch (OLC_ZONE(dsc)->cmd[i].command) {
          case 'P':
            OLC_ZONE(dsc)->cmd[i].arg3 += (OLC_ZONE(dsc)->cmd[i].arg3 >= robj_num);
            /* Fall through. */
          case 'E':
          case 'G':
          case 'O':
            OLC_ZONE(dsc)->cmd[i].arg1 += (OLC_ZONE(dsc)->cmd[i].arg1 >= robj_num);
            break;
          case 'R':
            OLC_ZONE(dsc)->cmd[i].arg2 += (OLC_ZONE(dsc)->cmd[i].arg2 >= robj_num);
            break;
          default:
          break;
        }
}

static void oedit_save_to_disk(int zone_num)
{
  save_objects(zone_num);
}

/* Menu functions */
/* For container flags. */
static void oedit_disp_container_flags_menu(struct descriptor_data *d)
{
  char bits[MAX_STRING_LENGTH];
  get_char_colors(d->character);
  clear_screen(d);

  sprintbit(GET_OBJ_VAL(OLC_OBJ(d), 1), container_bits, bits, sizeof(bits));
  write_to_output(d,
    "\n## Flags\r"
	  "\nmenu[closeable]:1\r"
	  "\nmenu[pickproof]:2\r"
	  "\nmenu[closed]:3\r"
	  "\nmenu[locked]:4\r"
	  "\nflags: %s\r"
    "\nmenu[done]:0\r",
	  bits);
}

/* For extra descriptions. */
static void oedit_disp_extradesc_menu(struct descriptor_data *d)
{
  struct extra_descr_data *extra_desc = OLC_DESC(d);

  get_char_colors(d->character);
  clear_screen(d);
  write_to_output(d,
	  "\n## Tags\r"
	  "\nselect[1:tag]:%s\r"
	  "\nselect[2:describe]:%s\r"
    "::begin:buttons"
	  "\nbmud[%s]:3\r"
    "::end:buttons"
	  "\nmenu[done]:0\r",

 	  (extra_desc->keyword && *extra_desc->keyword) ? extra_desc->keyword : "[none]",
    (extra_desc->description && *extra_desc->description) ? extra_desc->description : "[none]",
	  !extra_desc->next ? "new tag" : "next tag");
  OLC_MODE(d) = OEDIT_EXTRADESC_MENU;
}

/* Ask for *which* apply to edit. */
static void oedit_disp_prompt_apply_menu(struct descriptor_data *d)
{
  char apply_buf[MAX_STRING_LENGTH];
  int counter;

  get_char_colors(d->character);
  clear_screen(d);

  write_to_output(d, "\n## Affection\r"
    "\n::begin:buttons");

  for (counter = 0; counter < MAX_OBJ_AFFECT; counter++) {
    if (OLC_OBJ(d)->affected[counter].modifier) {
      sprinttype(OLC_OBJ(d)->affected[counter].location, apply_types, apply_buf, sizeof(apply_buf));
      write_to_output(d, "\nbmud[%d to %s]:%d\r",
	      OLC_OBJ(d)->affected[counter].modifier,
        apply_buf,
        counter + 1);
    } else {
      write_to_output(d, "\nmenu[None]:%d\r", counter + 1);
    }
  }

  write_to_output(d, "\n::end:buttons\r"
    "\nmenu[done]:0\r");

  OLC_MODE(d) = OEDIT_PROMPT_APPLY;
}

/* Ask for liquid type. */
static void oedit_liquid_type(struct descriptor_data *d)
{
  int i,count=0;
  get_char_colors(d->character);
  clear_screen(d);
  write_to_output(d, "\n## Liquid Type\r"
    "\n::begin:buttons\r");
  // column_list(d->character, 0, drinks, NUM_LIQ_TYPES, TRUE);
  for (i = 0; i < NUM_LIQ_TYPES; i++) {
    write_to_output(d, "\nbmud[%s]:%d\r", drinks[i], ++count);
  }
  write_to_output(d, "\n::end:buttons\r"
    "\nmenu[done]:0\r");
  OLC_MODE(d) = OEDIT_VALUE_3;
}

/* The actual apply to set. */
static void oedit_disp_apply_menu(struct descriptor_data *d)
{
  int i,count=0;
  get_char_colors(d->character);
  clear_screen(d);
  write_to_output(d, "\n## Apply Type\r"
    "\n::begin:buttons\r");
  // column_list(d->character, 0, apply_types, NUM_APPLIES, TRUE);
  for (i = 0; i < NUM_APPLIES; i++) {
    write_to_output(d, "\nbmud[%s]:%d\r", apply_types[i], ++count);
  }
  write_to_output(d, "\n::end:buttons\r"
    "\nmenu[done]:0\r");
  OLC_MODE(d) = OEDIT_APPLY;
}

/* Weapon type. */
static void oedit_disp_weapon_menu(struct descriptor_data *d)
{
  int counter;

  get_char_colors(d->character);
  clear_screen(d);

  for (counter = 0; counter < NUM_ATTACK_TYPES; counter++) {
    write_to_output(d, "\n[%s]:%d\r",
      attack_hit_text[counter].singular,
      counter
    );
  }
  write_to_output(d, "\nEnter weapon type:\r");
}

/* Spell type. */
static void oedit_disp_spells_menu(struct descriptor_data *d)
{
  int counter;

  get_char_colors(d->character);
  clear_screen(d);

  for (counter = 1; counter <= NUM_SPELLS; counter++) {
    write_to_output(d, "\nmenu[%s]:%d\r",
      spell_info[counter].name,
      counter
    );
  }
  write_to_output(d, "\nEnter spell choice (-1 for none)\r");
}

/* Object value #1 */
static void oedit_disp_val1_menu(struct descriptor_data *d)
{
  OLC_MODE(d) = OEDIT_VALUE_1;
  switch (GET_OBJ_TYPE(OLC_OBJ(d))) {
  case ITEM_LIGHT:
    /* values 0 and 1 are unused.. jump to 2 */
    oedit_disp_val3_menu(d);
    break;
  case ITEM_BOOK:
  case ITEM_SECURITY:
  case ITEM_MILITARY:
  case ITEM_MEDICAL:
    write_to_output(d, "\nWhat is the spell level?\r");
    break;
  case ITEM_TOOL:
    /* This doesn't seem to be used if I remember right. */
    write_to_output(d, "\nWhat is the modifier to hitroll?\r");
    break;
  case ITEM_ARMOR:
    write_to_output(d, "\nApply to AC?\r");
    break;
  case ITEM_CONTAINER:
    write_to_output(d, "\nWhat is the max weight it can contain? (-1 for unlimited)\r");
    break;
  case ITEM_DRINKCON:
  case ITEM_FOUNTAIN:
    write_to_output(d, "\nWhat are the max drink units? (-1 for unlimited)\r");
    break;
  case ITEM_FOOD:
    write_to_output(d, "\nHow many hours to fill stomach?\r");
    break;
  case ITEM_MONEY:
    write_to_output(d, "\nWhat are the total number?\r");
    break;
  case ITEM_FURNITURE:
    write_to_output(d, "\nHow many people can it hold?\r");
    break;
  case ITEM_NOTE:  // These object types have no 'values' so go back to menu
  case ITEM_OTHER:
  case ITEM_WORN:
  case ITEM_TREASURE:
  case ITEM_TRASH:
  case ITEM_KEY:
  case ITEM_PEN:
  case ITEM_BOAT:
  case ITEM_TECH:   /* Not implemented, but should be handled here */
  case ITEM_APPLIANCE:  /* Not implemented, but should be handled here */
    oedit_disp_menu(d);
    break;
  default:
    mudlog(BRF, LVL_BUILDER, TRUE, "SYSERR: OLC: Reached default case in oedit_disp_val1_menu()!");
    break;
  }
}

/* Object value #2 */
static void oedit_disp_val2_menu(struct descriptor_data *d)
{
  OLC_MODE(d) = OEDIT_VALUE_2;
  switch (GET_OBJ_TYPE(OLC_OBJ(d))) {
  case ITEM_BOOK:
  case ITEM_MEDICAL:
    oedit_disp_spells_menu(d);
    break;
  case ITEM_SECURITY:
  case ITEM_MILITARY:
    write_to_output(d, "\nWhat are the max number of charges?\r");
    break;
  case ITEM_TOOL:
    write_to_output(d, "\nHow many damage dice are there?\r");
    break;
  case ITEM_FOOD:
    /* Values 2 and 3 are unused, jump to 4...Odd. */
    oedit_disp_val4_menu(d);
    break;
  case ITEM_CONTAINER:
    /* These are flags, needs a bit of special handling. */
    oedit_disp_container_flags_menu(d);
    break;
  case ITEM_DRINKCON:
  case ITEM_FOUNTAIN:
    write_to_output(d, "\nHow many initial drink units are there?\r");
    break;
  default:
    oedit_disp_menu(d);
  }
}

/* Object value #3 */
static void oedit_disp_val3_menu(struct descriptor_data *d)
{
  OLC_MODE(d) = OEDIT_VALUE_3;
  switch (GET_OBJ_TYPE(OLC_OBJ(d))) {
  case ITEM_LIGHT:
    write_to_output(d, "\nHow many hours will it operate? (0 = burnt, -1 is infinite)\r");
    break;
  case ITEM_BOOK:
  case ITEM_MEDICAL:
    oedit_disp_spells_menu(d);
    break;
  case ITEM_SECURITY:
  case ITEM_MILITARY:
    write_to_output(d, "\nHow many charges are remaining?\r");
    break;
  case ITEM_TOOL:
    write_to_output(d, "\nWhat is the size of the damage dice?\r");
    break;
  case ITEM_CONTAINER:
    write_to_output(d, "\nWhat is the key vnum to open the container?(-1 for no key)?\r");
    break;
  case ITEM_DRINKCON:
  case ITEM_FOUNTAIN:
    oedit_liquid_type(d);
    break;
  default:
    oedit_disp_menu(d);
  }
}

/* Object value #4 */
static void oedit_disp_val4_menu(struct descriptor_data *d)
{
  OLC_MODE(d) = OEDIT_VALUE_4;
  switch (GET_OBJ_TYPE(OLC_OBJ(d))) {
  case ITEM_BOOK:
  case ITEM_MEDICAL:
  case ITEM_SECURITY:
  case ITEM_MILITARY:
    oedit_disp_spells_menu(d);
    break;
  case ITEM_TOOL:
    oedit_disp_weapon_menu(d);
    break;
  case ITEM_DRINKCON:
  case ITEM_FOUNTAIN:
  case ITEM_FOOD:
    write_to_output(d, "\nIs this item a poison? (0 = not poison)\r");
    break;
  default:
    oedit_disp_menu(d);
  }
}

/* Object type. */
static void oedit_disp_type_menu(struct descriptor_data *d)
{
  int i, count = 0;

  get_char_colors(d->character);
  clear_screen(d);

  write_to_output(d, "\n## Object Type\r"
    "\n::begin:buttons\r");

  for (i = 0; i < NUM_ITEM_TYPES; i++) {
    write_to_output(d, "\nbmud[%s]:%d\r", item_types[i], count++);
  }
  write_to_output(d, "\n::end:buttons:\r"
    "\nmenu[done]:0\r");
}

/* Object extra flags. */
static void oedit_disp_extra_menu(struct descriptor_data *d)
{
  char bits[MAX_STRING_LENGTH];
  int i, count = 0;

  get_char_colors(d->character);
  clear_screen(d);

  write_to_output(d, "\n## Object Flags\r"
    "\n::begin:buttons\r");

  for (i = 0; i < NUM_ITEM_FLAGS; i++) {
    write_to_output(d, "\nbmud[%s]:%d\r", extra_bits[i], ++count);
  }

  sprintbitarray(GET_OBJ_EXTRA(OLC_OBJ(d)), extra_bits, EF_ARRAY_MAX, bits);

  write_to_output(d, "\n::end:buttons\r"
    "\nflags: %s\r"
    "\nmenu[done]:0\r",
    bits
  );
}

/* Object perm flags. */
static void oedit_disp_perm_menu(struct descriptor_data *d)
{
  char bits[MAX_STRING_LENGTH];
  int i, count = 0;

  get_char_colors(d->character);
  clear_screen(d);

  write_to_output(d, "\n## Affects\r"
    "\n::begin:buttons\r");

  for (i = 1; i < NUM_AFF_FLAGS; i++) {
    write_to_output(d, "\nbmud[%s]:%d\r", affected_bits[i], ++count);
  }

  sprintbitarray(GET_OBJ_AFFECT(OLC_OBJ(d)), affected_bits, EF_ARRAY_MAX, bits);
  write_to_output(d, "\n::end:buttons\r"
    "\nflags: %s\r"
    "\nmenu[quit]:0\r",
    bits);
}

/* Object wear flags. */
static void oedit_disp_wear_menu(struct descriptor_data *d)
{
  char bits[MAX_STRING_LENGTH];
  int i, count = 0;

  get_char_colors(d->character);
  clear_screen(d);
  write_to_output(d, "\n## Wear Flags\r"
    "\n::begin:buttons\r");

  for (i = 0; i < NUM_ITEM_WEARS; i++) {
    write_to_output(d, "\nbmud[%s]:%d\r", wear_bits[i], ++count);
  }
  sprintbitarray(GET_OBJ_WEAR(OLC_OBJ(d)), wear_bits, TW_ARRAY_MAX, bits);
  write_to_output(d, "\n::end:buttons\r"
    "\nflags: %s\r"
    "\nmenu[quit]:0\r",
    bits);
}

/* Display main menu. */
static void oedit_disp_menu(struct descriptor_data *d)
{
  char buf1[MAX_STRING_LENGTH];
  char buf2[MAX_STRING_LENGTH];
  struct obj_data *obj;

  obj = OLC_OBJ(d);
  get_char_colors(d->character);
  clear_screen(d);

  /* Build buffers for first part of menu. */
  sprinttype(GET_OBJ_TYPE(obj), item_types, buf1, sizeof(buf1));
  sprintbitarray(GET_OBJ_EXTRA(obj), extra_bits, EF_ARRAY_MAX, buf2);

  /* Build first half of menu. */
  write_to_output(d,
    "\n# Object: %d\r"
	  "\nselect[a:keywords]:%s\r"
	  "\nselect[b:name]:%s\r"
	  "\nselect[c:avatar]:%s\r"
	  "\nselect[d:look]:%s\r"
	  "\nselect[e:type]:%s\r"
	  "\nselect[f:flags]:%s\r",
	  OLC_NUM(d),
	  (obj->name && *obj->name) ? obj->name : "undefined",
	  (obj->short_description && *obj->short_description) ? obj->short_description : "undefined",
	  (obj->description && *obj->description) ? obj->description : "undefined",
	  (obj->action_description && *obj->action_description) ? obj->action_description : "Not Set.",
	  buf1,
	  buf2
	  );

  /* Send first half then build second half of menu. */
  sprintbitarray(GET_OBJ_WEAR(OLC_OBJ(d)), wear_bits, EF_ARRAY_MAX, buf1);
  sprintbitarray(GET_OBJ_AFFECT(OLC_OBJ(d)), affected_bits, EF_ARRAY_MAX, buf2);

  write_to_output(d,
	  "\nselect[g:wear]:%s\r"
    "\nselect[h:affects]:%s\r"
	  "\nselect[i:weight]:%d\r"
	  "\nselect[j:cost]:%d\r"
	  "\nselect[k:rent]:%d\r"
	  "\nselect[l:timer]:%d\r"
    "\nselect[m:min level]:%d\r"
	  "\nselect[n:liquid]:%d %d %d %d\r"
    "\n::begin:buttons\r"
    "\nbmud[tags%s]:1\r"
	  "\nbmud[triggers%s]:2\r"
    "\nbmud[applies to]:3\r"
    "\nbmud[copy object]:4\r"
    "\nbmud[delete object]:5\r"
    "\n::end:buttons\r"
	  "\nmenu[quit]:0\r",
	  buf1,                  //wear
    buf2,                 // affects
	  GET_OBJ_WEIGHT(obj),  //weight
	  GET_OBJ_COST(obj),     // cost
	  GET_OBJ_RENT(obj),     // rent
	  GET_OBJ_TIMER(obj),    //timer
    GET_OBJ_LEVEL(obj),     // minimum level
	  GET_OBJ_VAL(obj, 0),     // liquid
	  GET_OBJ_VAL(obj, 1),     // liquid
	  GET_OBJ_VAL(obj, 2),   // liquid
	  GET_OBJ_VAL(obj, 3),   // liquid
	  obj->ex_description ? "*" : "", // tags
    OLC_SCRIPT(d) ? "*" : "");  // triggers
    OLC_MODE(d) = OEDIT_MAIN_MENU;  //set mode
}

/* main loop (of sorts).. basically interpreter throws all input to here. */
void oedit_parse(struct descriptor_data *d, char *arg)
{
  int number, max_val, min_val;
  char *oldtext = NULL;

  switch (OLC_MODE(d)) {

  case OEDIT_CONFIRM_SAVESTRING:
    switch (*arg) {
    case 'y':
    case 'Y':
      oedit_save_internally(d);
      mudlog(CMP, MAX(LVL_BUILDER, GET_INVIS_LEV(d->character)), TRUE,
              "OLC: %s edits obj %d", GET_NAME(d->character), OLC_NUM(d));
      if (CONFIG_OLC_SAVE) {
        oedit_save_to_disk(real_zone_by_thing(OLC_NUM(d)));
        write_to_output(d, "\nsave:Object saved to disk.\r");
      } else
        write_to_output(d, "\nsave:Object saved to memory.\r");
      cleanup_olc(d, CLEANUP_ALL);
      return;
    case 'n':
    case 'N':
      write_to_output(d, "\nsave:Cancel.\r");
      /* If not saving, we must free the script_proto list. */
      OLC_OBJ(d)->proto_script = OLC_SCRIPT(d);
      free_proto_script(OLC_OBJ(d), OBJ_TRIGGER);
      cleanup_olc(d, CLEANUP_ALL);
      return;
    case 'a': /* abort quit */
    case 'A':
      write_to_output(d, "\nsave:Abort.\r");
      oedit_disp_menu(d);
      return;
    default:
      write_to_output(d, "\ninfo:Invalid choice!\r");
      write_to_output(d, "%s", confirm_msg);
      return;
    }

  case OEDIT_MAIN_MENU:
    /* Throw us out to whichever edit mode based on user input. */
    switch (*arg) {
    case '0':
      if (OLC_VAL(d)) {	/* Something has been modified. */
        write_to_output(d, "%s", confirm_msg);
        OLC_MODE(d) = OEDIT_CONFIRM_SAVESTRING;
      } else {
        write_to_output(d, "\nsave:Object unchanged.\r");
        cleanup_olc(d, CLEANUP_ALL);
      }
      return;
    case '1':
      /* If extra descriptions don't exist. */
      if (OLC_OBJ(d)->ex_description == NULL) {
        CREATE(OLC_OBJ(d)->ex_description, struct extra_descr_data, 1);
        OLC_OBJ(d)->ex_description->next = NULL;
      }
      OLC_DESC(d) = OLC_OBJ(d)->ex_description;
      oedit_disp_extradesc_menu(d);
      break;
    case '2':
      OLC_SCRIPT_EDIT_MODE(d) = SCRIPT_MAIN_MENU;
      dg_script_menu(d);
      return;
    case '3':
      oedit_disp_prompt_apply_menu(d);
      break;
    case '4':
      write_to_output(d, "\nWhat object would you like to copy?\r");
      OLC_MODE(d) = OEDIT_COPY;
      break;
    case '5':
      write_to_output(d, "\n## Delete Object\r"
        "\np:Do you wish to delete this Object?\r"
        "%s",
        confirm_btn);
      OLC_MODE(d) = OEDIT_DELETE;
      break;
    case 'a':
      write_to_output(d, "\nWhat are the object keywords?\r"
        "\ncurrent:%s\r",
        (OLC_OBJ(d)->name) ? OLC_OBJ(d)->name : "undefined");
      OLC_MODE(d) = OEDIT_KEYWORD;
      break;
    case 'b':
      write_to_output(d, "\nWhat is the object name?\r"
        "\ncurrent:%s\r",
        (OLC_OBJ(d)->short_description) ? OLC_OBJ(d)->short_description : "undefined");
      OLC_MODE(d) = OEDIT_SHORTDESC;
      break;
    case 'c':
      write_to_output(d, "\nWhat is the object description?\r"
        "\ncurrent:%s\r",
        (OLC_OBJ(d)->description) ? OLC_OBJ(d)->description : "undefined");
      OLC_MODE(d) = OEDIT_LONGDESC;
      break;
    case 'd':
      OLC_MODE(d) = OEDIT_ACTDESC;
      send_editor_help(d);
      write_to_output(d, "\nWhat is the object action?\r");
      if (OLC_OBJ(d)->action_description) {
        write_to_output(d, "%s", OLC_OBJ(d)->action_description);
	      oldtext = strdup(OLC_OBJ(d)->action_description);
      }
      string_write(d, &OLC_OBJ(d)->action_description, MAX_MESSAGE_LENGTH, 0, oldtext);
      OLC_VAL(d) = 1;
      break;
    case 'e':
      oedit_disp_type_menu(d);
      OLC_MODE(d) = OEDIT_TYPE;
      break;
    case 'f':
      oedit_disp_extra_menu(d);
      OLC_MODE(d) = OEDIT_EXTRAS;
      break;
    case 'g':
      oedit_disp_wear_menu(d);
      OLC_MODE(d) = OEDIT_WEAR;
      break;
    case 'h':
      oedit_disp_perm_menu(d);
      OLC_MODE(d) = OEDIT_PERM;
      break;
    case 'i':
      write_to_output(d, "\nWhat is the object weight?\r"
      "\ncurrent:%d\r",
      GET_OBJ_WEIGHT(OLC_OBJ(d)));
      OLC_MODE(d) = OEDIT_WEIGHT;
      break;
    case 'j':
      write_to_output(d, "\nWhat is the object cost?\r"
        "\ncurrent:%d\r",
        GET_OBJ_COST(OLC_OBJ(d)));
      OLC_MODE(d) = OEDIT_COST;
      break;
    case 'k':
      write_to_output(d, "\nWhat is the object rent?\r"
        "\ncurrent:%d\r",
        GET_OBJ_RENT(OLC_OBJ(d)));
      OLC_MODE(d) = OEDIT_COSTPERDAY;
      break;
    case 'l':
      write_to_output(d, "What is the object timer?\r"
        "\ncurrent:%d\r",
        GET_OBJ_TIMER(OLC_OBJ(d)));
      OLC_MODE(d) = OEDIT_TIMER;
      break;
    case 'm':
      write_to_output(d, "\nWhat is the object minimum level?\r"
        "\ncurrent:%d",
        GET_OBJ_LEVEL(OLC_OBJ(d)));
      OLC_MODE(d) = OEDIT_LEVEL;
      break;
    case 'n':
      /* Clear any old values */
      GET_OBJ_VAL(OLC_OBJ(d), 0) = 0;
      GET_OBJ_VAL(OLC_OBJ(d), 1) = 0;
      GET_OBJ_VAL(OLC_OBJ(d), 2) = 0;
      GET_OBJ_VAL(OLC_OBJ(d), 3) = 0;
      OLC_VAL(d) = 1;
      oedit_disp_val1_menu(d);
      break;
    default:
      oedit_disp_menu(d);
      break;
    }
    return; /* end of OEDIT_MAIN_MENU */

  case OLC_SCRIPT_EDIT:
    if (dg_script_edit_parse(d, arg)) return;
    break;

  case OEDIT_KEYWORD:
    if (!genolc_checkstring(d, arg))
      break;
    if (OLC_OBJ(d)->name)
      free(OLC_OBJ(d)->name);
    OLC_OBJ(d)->name = str_udup(arg);
    break;

  case OEDIT_SHORTDESC:
    if (!genolc_checkstring(d, arg))
      break;
    if (OLC_OBJ(d)->short_description)
      free(OLC_OBJ(d)->short_description);
    OLC_OBJ(d)->short_description = str_udup(arg);
    break;

  case OEDIT_LONGDESC:
    if (!genolc_checkstring(d, arg))
      break;
    if (OLC_OBJ(d)->description)
      free(OLC_OBJ(d)->description);
    OLC_OBJ(d)->description = str_udup(arg);
    break;

  case OEDIT_TYPE:
    number = atoi(arg);
    if ((number < 0) || (number >= NUM_ITEM_TYPES)) {
      write_to_output(d, "\ninfo:Invalid choice, please try again.\r");
      return;
    } else
      GET_OBJ_TYPE(OLC_OBJ(d)) = number;
    /* what's the boundschecking worth if we don't do this ? -- Welcor */
    GET_OBJ_VAL(OLC_OBJ(d), 0) = GET_OBJ_VAL(OLC_OBJ(d), 1) =
    GET_OBJ_VAL(OLC_OBJ(d), 2) = GET_OBJ_VAL(OLC_OBJ(d), 3) = 0;
    break;

  case OEDIT_EXTRAS:
    number = atoi(arg);
    if ((number < 0) || (number > NUM_ITEM_FLAGS)) {
      oedit_disp_extra_menu(d);
      return;
    } else if (number == 0)
      break;
    else {
      TOGGLE_BIT_AR(GET_OBJ_EXTRA(OLC_OBJ(d)), (number - 1));
      oedit_disp_extra_menu(d);
      return;
    }

  case OEDIT_WEAR:
    number = atoi(arg);
    if ((number < 0) || (number > NUM_ITEM_WEARS)) {
      write_to_output(d, "\ninfo:That's not a valid choice!\r");
      oedit_disp_wear_menu(d);
      return;
    } else if (number == 0)	/* Quit. */
      break;
    else {
      TOGGLE_BIT_AR(GET_OBJ_WEAR(OLC_OBJ(d)), (number - 1));
      oedit_disp_wear_menu(d);
      return;
    }

  case OEDIT_WEIGHT:
    GET_OBJ_WEIGHT(OLC_OBJ(d)) = LIMIT(atoi(arg), 0, MAX_OBJ_WEIGHT);
    break;

  case OEDIT_COST:
    GET_OBJ_COST(OLC_OBJ(d)) = LIMIT(atoi(arg), 0, MAX_OBJ_COST);
    break;

  case OEDIT_COSTPERDAY:
    GET_OBJ_RENT(OLC_OBJ(d)) = LIMIT(atoi(arg), 0, MAX_OBJ_RENT);
    break;

  case OEDIT_TIMER:
    GET_OBJ_TIMER(OLC_OBJ(d)) = LIMIT(atoi(arg), 0, MAX_OBJ_TIMER);
    break;

  case OEDIT_LEVEL:
    GET_OBJ_LEVEL(OLC_OBJ(d)) = LIMIT(atoi(arg), 0, LVL_IMPL);
    break;

  case OEDIT_PERM:
    if ((number = atoi(arg)) == 0)
      break;
    if (number > 0 && number < NUM_AFF_FLAGS) {
      /* Setting AFF_CHARM on objects like this is dangerous. */
      if (number != AFF_CHARM) {
        TOGGLE_BIT_AR(GET_OBJ_AFFECT(OLC_OBJ(d)), number);
      }
    }
    oedit_disp_perm_menu(d);
    return;

  case OEDIT_VALUE_1:
    number = atoi(arg);
    switch (GET_OBJ_TYPE(OLC_OBJ(d))) {
    case ITEM_FURNITURE:
      if (number < 0 || number > MAX_PEOPLE)
        oedit_disp_val1_menu(d);
      else {
        GET_OBJ_VAL(OLC_OBJ(d), 0) = number;
        oedit_disp_val2_menu(d);
      }
      break;
    case ITEM_TOOL:
      GET_OBJ_VAL(OLC_OBJ(d), 0) = MIN(MAX(atoi(arg), -50), 50);
      break;
    case ITEM_CONTAINER:
      GET_OBJ_VAL(OLC_OBJ(d), 0) = LIMIT(atoi(arg), -1, MAX_CONTAINER_SIZE);
      break;
    default:
      GET_OBJ_VAL(OLC_OBJ(d), 0) = atoi(arg);
    }
    /* proceed to menu 2 */
    oedit_disp_val2_menu(d);
    return;
  case OEDIT_VALUE_2:
    /* Here, I do need to check for out of range values. */
    number = atoi(arg);
    switch (GET_OBJ_TYPE(OLC_OBJ(d))) {
    case ITEM_BOOK:
    case ITEM_MEDICAL:
      if (number == 0 || number == -1)
	GET_OBJ_VAL(OLC_OBJ(d), 1) = -1;
      else
	GET_OBJ_VAL(OLC_OBJ(d), 1) = LIMIT(number, 1, NUM_SPELLS);

      oedit_disp_val3_menu(d);
      break;
    case ITEM_CONTAINER:
      /* Needs some special handling since we are dealing with flag values here. */
      if (number < 0 || number > 4)
	oedit_disp_container_flags_menu(d);
      else if (number != 0) {
        TOGGLE_BIT(GET_OBJ_VAL(OLC_OBJ(d), 1), 1 << (number - 1));
        OLC_VAL(d) = 1;
	oedit_disp_val2_menu(d);
      } else
	oedit_disp_val3_menu(d);
      break;
    case ITEM_TOOL:
      GET_OBJ_VAL(OLC_OBJ(d), 1) = LIMIT(number, 1, MAX_WEAPON_NDICE);
      oedit_disp_val3_menu(d);
      break;

    default:
      GET_OBJ_VAL(OLC_OBJ(d), 1) = number;
      oedit_disp_val3_menu(d);
    }
    return;

  case OEDIT_VALUE_3:
    number = atoi(arg);
    /* Quick'n'easy error checking. */
    switch (GET_OBJ_TYPE(OLC_OBJ(d))) {
    case ITEM_BOOK:
    case ITEM_MEDICAL:
      if (number == 0 || number == -1) {
	GET_OBJ_VAL(OLC_OBJ(d), 2) = -1;
	oedit_disp_val4_menu(d);
	return;
      }
      min_val = 1;
      max_val = NUM_SPELLS;
      break;
    case ITEM_TOOL:
      min_val = 1;
      max_val = MAX_WEAPON_SDICE;
      break;
    case ITEM_SECURITY:
    case ITEM_MILITARY:
      min_val = 0;
      max_val = 20;
      break;
    case ITEM_DRINKCON:
    case ITEM_FOUNTAIN:
      min_val = 0;
      max_val = NUM_LIQ_TYPES - 1;
      number--;
      break;
    case ITEM_KEY:
      min_val = 0;
      max_val = 65099;
      break;
    default:
      min_val = -65000;
      max_val = 65000;
    }
    GET_OBJ_VAL(OLC_OBJ(d), 2) = LIMIT(number, min_val, max_val);
    oedit_disp_val4_menu(d);
    return;

  case OEDIT_VALUE_4:
    number = atoi(arg);
    switch (GET_OBJ_TYPE(OLC_OBJ(d))) {
    case ITEM_BOOK:
    case ITEM_MEDICAL:
      if (number == 0 || number == -1) {
	GET_OBJ_VAL(OLC_OBJ(d), 3) = -1;
        oedit_disp_menu(d);
	return;
      }
      min_val = 1;
      max_val = NUM_SPELLS;
      break;
    case ITEM_SECURITY:
    case ITEM_MILITARY:
      min_val = 1;
      max_val = NUM_SPELLS;
      break;
    case ITEM_TOOL:
      min_val = 0;
      max_val = NUM_ATTACK_TYPES - 1;
      break;
    default:
      min_val = -65000;
      max_val = 65000;
      break;
    }
    GET_OBJ_VAL(OLC_OBJ(d), 3) = LIMIT(number, min_val, max_val);
    break;

  case OEDIT_PROMPT_APPLY:
    if ((number = atoi(arg)) == 0)
      break;
    else if (number < 0 || number > MAX_OBJ_AFFECT) {
      oedit_disp_prompt_apply_menu(d);
      return;
    }
    OLC_VAL(d) = number - 1;
    OLC_MODE(d) = OEDIT_APPLY;
    oedit_disp_apply_menu(d);
    return;

  case OEDIT_APPLY:
    if (((number = atoi(arg)) == 0) || ((number = atoi(arg)) == 1)) {
      OLC_OBJ(d)->affected[OLC_VAL(d)].location = 0;
      OLC_OBJ(d)->affected[OLC_VAL(d)].modifier = 0;
      oedit_disp_prompt_apply_menu(d);
    } else if (number < 0 || number > NUM_APPLIES)
      oedit_disp_apply_menu(d);
    else {
      int counter;

      /* add in check here if already applied.. deny builders another */
      if (GET_LEVEL(d->character) < LVL_IMPL) {
        for (counter = 0; counter < MAX_OBJ_AFFECT; counter++) {
          if (OLC_OBJ(d)->affected[counter].location == number) {
            write_to_output(d, "\nObject already has that apply.\r");
            return;
          }
        }
      }

      OLC_OBJ(d)->affected[OLC_VAL(d)].location = number - 1;
      write_to_output(d, "\nModifier:\r");
      OLC_MODE(d) = OEDIT_APPLYMOD;
    }
    return;

  case OEDIT_APPLYMOD:
    OLC_OBJ(d)->affected[OLC_VAL(d)].modifier = atoi(arg);
    oedit_disp_prompt_apply_menu(d);
    return;

  case OEDIT_EXTRADESC_KEY:
    if (genolc_checkstring(d, arg)) {
      if (OLC_DESC(d)->keyword)
        free(OLC_DESC(d)->keyword);
      OLC_DESC(d)->keyword = str_udup(arg);
    }
    oedit_disp_extradesc_menu(d);
    return;

  case OEDIT_EXTRADESC_MENU:
    switch ((number = atoi(arg))) {
    case 0:
      if (!OLC_DESC(d)->keyword || !OLC_DESC(d)->description) {
        struct extra_descr_data *temp;

	      if (OLC_DESC(d)->keyword) {
          free(OLC_DESC(d)->keyword);
        }
	      if (OLC_DESC(d)->description) {
          free(OLC_DESC(d)->description);
        }

	      /* Clean up pointers */
	      REMOVE_FROM_LIST(OLC_DESC(d), OLC_OBJ(d)->ex_description, next);
	      free(OLC_DESC(d));
	      OLC_DESC(d) = NULL;
      }
      break;

    case 1:
      OLC_MODE(d) = OEDIT_EXTRADESC_KEY;
      write_to_output(d, "\nWhat is the tag?\r");
      return;

    case 2:
      OLC_MODE(d) = OEDIT_EXTRADESC_DESCRIPTION;
      send_editor_help(d);
      write_to_output(d, "\nWhat is the path?\r");
      if (OLC_DESC(d)->description) {
        write_to_output(d, "%s", OLC_DESC(d)->description);
        oldtext = strdup(OLC_DESC(d)->description);
      }
      string_write(d, &OLC_DESC(d)->description, MAX_MESSAGE_LENGTH, 0, oldtext);
      OLC_VAL(d) = 1;
      return;

    case 3:
      /* Only go to the next description if this one is finished. */
      if (OLC_DESC(d)->keyword && OLC_DESC(d)->description) {
	       struct extra_descr_data *new_extra;

         if (OLC_DESC(d)->next) {
           OLC_DESC(d) = OLC_DESC(d)->next;
         }
         else {	/* Make new extra description and attach at end. */
          CREATE(new_extra, struct extra_descr_data, 1);
          OLC_DESC(d)->next = new_extra;
          OLC_DESC(d) = OLC_DESC(d)->next;
        }
      }
      /* No break - drop into default case. */
    default:
      oedit_disp_extradesc_menu(d);
      return;
    }
    break;

  case OEDIT_COPY:
    if ((number = real_object(atoi(arg))) != NOTHING) {
      oedit_setup_existing(d, number);
    } else
      write_to_output(d, "\ninfo:That object does not exist.\r");
    break;

  case OEDIT_DELETE:
    if (*arg == 'y' || *arg == 'Y') {
      if (delete_object(GET_OBJ_RNUM(OLC_OBJ(d))) != NOTHING)
        write_to_output(d, "\ninfo:Object deleted.\r");
      else
        write_to_output(d, "\ninfo:That object could not be deleted.\r");

      cleanup_olc(d, CLEANUP_ALL);
    } else if (*arg == 'n' || *arg == 'N') {
      oedit_disp_menu(d);
      OLC_MODE(d) = OEDIT_MAIN_MENU;
    } else
      write_to_output(d, "\ninfo:Please answer 'Y' or 'N'\r");
    return;
  default:
    mudlog(BRF, LVL_BUILDER, TRUE, "SYSERR: OLC: Reached default case in oedit_parse()!\r\n");
    write_to_output(d, "\nOops...\r");
    break;
  }

  /* If we get here, we have changed something. */
  OLC_VAL(d) = 1;
  oedit_disp_menu(d);
}

void oedit_string_cleanup(struct descriptor_data *d, int terminator)
{
  switch (OLC_MODE(d)) {
  case OEDIT_ACTDESC:
    oedit_disp_menu(d);
    break;
  case OEDIT_EXTRADESC_DESCRIPTION:
    oedit_disp_extradesc_menu(d);
    break;
  }
}
