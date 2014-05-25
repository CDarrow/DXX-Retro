/*
THE COMPUTER CODE CONTAINED HEREIN IS THE SOLE PROPERTY OF PARALLAX
SOFTWARE CORPORATION ("PARALLAX").  PARALLAX, IN DISTRIBUTING THE CODE TO
END-USERS, AND SUBJECT TO ALL OF THE TERMS AND CONDITIONS HEREIN, GRANTS A
ROYALTY-FREE, PERPETUAL LICENSE TO SUCH END-USERS FOR USE BY SUCH END-USERS
IN USING, DISPLAYING,  AND CREATING DERIVATIVE WORKS THEREOF, SO LONG AS
SUCH USE, DISPLAY OR CREATION IS FOR NON-COMMERCIAL, ROYALTY OR REVENUE
FREE PURPOSES.  IN NO EVENT SHALL THE END-USER USE THE COMPUTER CODE
CONTAINED HEREIN FOR REVENUE-BEARING PURPOSES.  THE END-USER UNDERSTANDS
AND AGREES TO THE TERMS HEREIN AND ACCEPTS THE SAME BY USE OF THIS FILE.
COPYRIGHT 1993-1999 PARALLAX SOFTWARE CORPORATION.  ALL RIGHTS RESERVED.
*/

/*
 *
 * Stuff for rendering the HUD
 *
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "timer.h"
#include "pstypes.h"
#include "console.h"
#include "inferno.h"
#include "dxxerror.h"
#include "gr.h"
#include "palette.h"
#include "bm.h"
#include "player.h"
#include "render.h"
#include "menu.h"
#include "newmenu.h"
#include "screens.h"
#include "fix.h"
#include "robot.h"
#include "game.h"
#include "gauges.h"
#include "gamefont.h"
#include "newdemo.h"
#include "text.h"
#include "multi.h"
#include "endlevel.h"
#include "cntrlcen.h"
#include "powerup.h"
#include "laser.h"
#include "playsave.h"
#include "automap.h"
#include "mission.h"
#include "gameseq.h"
#include "args.h"

#ifdef OGL
#include "ogl_init.h"
#endif

extern int LinearSVGABuffer;

extern void newmenu_free_background();
int netplayerinfo_on=0;

extern ubyte DefiningMarkerMessage;

void game_draw_marker_message()
{
	if ( DefiningMarkerMessage)
	{
		gr_set_curfont(GAME_FONT);
		gr_set_fontcolor(BM_XRGB(0,63,0),-1);
		gr_printf(0x8000, (LINE_SPACING*5)+FSPACY(1), "Marker: %s_", Marker_input );
	}

}

#ifdef NETWORK
void game_draw_multi_message()
{
	if ( (Game_mode&GM_MULTI) && (multi_sending_message[Player_num]))	{
		gr_set_curfont(GAME_FONT);
		gr_set_fontcolor(BM_XRGB(0,63,0),-1);
		gr_printf(0x8000, (LINE_SPACING*5)+FSPACY(1), "%s: %s_", TXT_MESSAGE, Network_message );
	}

	if ( (Game_mode&GM_MULTI) && (multi_defining_message))	{
		gr_set_curfont(GAME_FONT);
		gr_set_fontcolor(BM_XRGB(0,63,0),-1);
		gr_printf(0x8000, (LINE_SPACING*5)+FSPACY(1), "%s #%d: %s_", TXT_MACRO, multi_defining_message, Network_message );
	}
}
#endif

void show_framerate()
{
	static int fps_count = 0, fps_rate = 0;
	int y = GHEIGHT;
	static fix64 fps_time = 0;

	gr_set_curfont(GAME_FONT);
	gr_set_fontcolor(BM_XRGB(0,31,0),-1);

	if (PlayerCfg.CockpitMode[1] == CM_FULL_SCREEN) {
		if ((Game_mode & GM_MULTI) || (Newdemo_state == ND_STATE_PLAYBACK && Newdemo_game_mode & GM_MULTI))
			y -= LINE_SPACING * 10;
		else
			y -= LINE_SPACING * 4;
	} else if (PlayerCfg.CockpitMode[1] == CM_STATUS_BAR) {
		if ((Game_mode & GM_MULTI) || (Newdemo_state == ND_STATE_PLAYBACK && Newdemo_game_mode & GM_MULTI))
			y -= LINE_SPACING * 6;
		else
			y -= LINE_SPACING * 1;
	} else {
		if ((Game_mode & GM_MULTI) || (Newdemo_state == ND_STATE_PLAYBACK && Newdemo_game_mode & GM_MULTI))
			y -= LINE_SPACING * 7;
		else
			y -= LINE_SPACING * 2;
	}

	fps_count++;
	if (timer_query() >= fps_time + F1_0)
	{
		fps_rate = fps_count;
		fps_count = 0;
		fps_time = timer_query();
	}
	gr_printf(SWIDTH-(GameArg.SysMaxFPS>999?FSPACX(43):FSPACX(37)),y,"FPS: %i",fps_rate);
}

#ifdef NETWORK
void show_netplayerinfo()
{
	int x=0, y=0, i=0, color=0, eff=0;
	static const char *const eff_strings[]={"trashing","really hurting","seriously effecting","hurting","effecting","tarnishing"};

	gr_set_current_canvas(NULL);
	gr_set_curfont(GAME_FONT);
	gr_set_fontcolor(255,-1);

	x=(SWIDTH/2)-FSPACX(120);
	y=(SHEIGHT/2)-FSPACY(84);

	gr_settransblend(14, GR_BLEND_NORMAL);
	gr_setcolor( BM_XRGB(0,0,0) );
	gr_rect((SWIDTH/2)-FSPACX(120),(SHEIGHT/2)-FSPACY(84),(SWIDTH/2)+FSPACX(120),(SHEIGHT/2)+FSPACY(84));
	gr_settransblend(GR_FADE_OFF, GR_BLEND_NORMAL);

	// general game information
	y+=LINE_SPACING;
	gr_printf(0x8000,y,"%s",Netgame.game_name);
	y+=LINE_SPACING;
	gr_printf(0x8000,y,"%s - lvl: %i",Netgame.mission_title,Netgame.levelnum);

	x+=FSPACX(8);
	y+=LINE_SPACING*2;
	unsigned gamemode = Netgame.gamemode;
	gr_printf(x,y,"game mode: %s",gamemode < (sizeof(GMNames) / sizeof(GMNames[0])) ? GMNames[gamemode] : "INVALID");
	y+=LINE_SPACING;
	gr_printf(x,y,"difficulty: %s",MENU_DIFFICULTY_TEXT(Netgame.difficulty));
	y+=LINE_SPACING;
	gr_printf(x,y,"level time: %i:%02i:%02i",Players[Player_num].hours_level,f2i(Players[Player_num].time_level) / 60 % 60,f2i(Players[Player_num].time_level) % 60);
	y+=LINE_SPACING;
	gr_printf(x,y,"total time: %i:%02i:%02i",Players[Player_num].hours_total,f2i(Players[Player_num].time_total) / 60 % 60,f2i(Players[Player_num].time_total) % 60);
	y+=LINE_SPACING;
	if (Netgame.KillGoal)
		gr_printf(x,y,"Kill goal: %d",Netgame.KillGoal*5);

	// player information (name, kills, ping, game efficiency)
	y+=LINE_SPACING*2;
	gr_printf(x,y,"player");
	if (Game_mode & GM_MULTI_COOP)
		gr_printf(x+FSPACX(8)*7,y,"score");
	else
	{
		gr_printf(x+FSPACX(8)*7,y,"kills");
		gr_printf(x+FSPACX(8)*12,y,"deaths");
	}
	gr_printf(x+FSPACX(8)*18,y,"ping");
	gr_printf(x+FSPACX(8)*23,y,"efficiency");

	// process players table
	for (i=0; i<MAX_PLAYERS; i++)
	{
		if (!Players[i].connected)
			continue;

		y+=LINE_SPACING;

		if (Game_mode & GM_TEAM)
			color=get_team(i);
		else
			color=i;
		gr_set_fontcolor( BM_XRGB(player_rgb[color].r,player_rgb[color].g,player_rgb[color].b),-1 );
		gr_printf(x,y,"%s\n",Players[i].callsign);
		if (Game_mode & GM_MULTI_COOP)
			gr_printf(x+FSPACX(8)*7,y,"%-6d",Players[i].score);
		else
		{
			gr_printf(x+FSPACX(8)*7,y,"%-6d",Players[i].net_kills_total);
			gr_printf(x+FSPACX(8)*12,y,"%-6d",Players[i].net_killed_total);
		}

		gr_printf(x+FSPACX(8)*18,y,"%-6d",Netgame.players[i].ping);
		if (i != Player_num)
			gr_printf(x+FSPACX(8)*23,y,"%d/%d",kill_matrix[Player_num][i],kill_matrix[i][Player_num]);
	}

	y+=(LINE_SPACING*2)+(LINE_SPACING*(MAX_PLAYERS-N_players));

	// printf team scores
	if (Game_mode & GM_TEAM)
	{
		gr_set_fontcolor(255,-1);
		gr_printf(x,y,"team");
		gr_printf(x+FSPACX(8)*8,y,"score");
		y+=LINE_SPACING;
		gr_set_fontcolor(BM_XRGB(player_rgb[0].r,player_rgb[0].g,player_rgb[0].b),-1 );
		gr_printf(x,y,"%s:",Netgame.team_name[0]);
		gr_printf(x+FSPACX(8)*8,y,"%i",team_kills[0]);
		y+=LINE_SPACING;
		gr_set_fontcolor(BM_XRGB(player_rgb[1].r,player_rgb[1].g,player_rgb[1].b),-1 );
		gr_printf(x,y,"%s:",Netgame.team_name[1]);
		gr_printf(x+FSPACX(8)*8,y,"%i",team_kills[1]);
		y+=LINE_SPACING*2;
	}
	else
		y+=LINE_SPACING*4;

	gr_set_fontcolor(255,-1);

	// additional information about game - hoard, ranking
	eff=(int)((float)((float)PlayerCfg.NetlifeKills/((float)PlayerCfg.NetlifeKilled+(float)PlayerCfg.NetlifeKills))*100.0);
	if (eff<0)
		eff=0;

	if (Game_mode & GM_HOARD)
	{
		if (PhallicMan==-1)
			gr_printf(0x8000,y,"There is no record yet for this level."); 
		else
			gr_printf(0x8000,y,"%s has the record at %d points.",Players[PhallicMan].callsign,PhallicLimit);
	}
	else if (!PlayerCfg.NoRankings)
	{
		gr_printf(0x8000,y,"Your lifetime efficiency of %d%% (%d/%d)",eff,PlayerCfg.NetlifeKills,PlayerCfg.NetlifeKilled);
		y+=LINE_SPACING;
		if (eff<60)
			gr_printf(0x8000,y,"is %s your ranking.",eff_strings[eff/10]);
		else
			gr_printf(0x8000,y,"is serving you well.");
		y+=LINE_SPACING;
		gr_printf(0x8000,y,"your rank is: %s",RankStrings[GetMyNetRanking()]);
	}
}
#endif

#ifndef NDEBUG

fix Show_view_text_timer = -1;

void draw_window_label()
{
	if ( Show_view_text_timer > 0 )
	{
		char *viewer_name,*control_name;
		char	*viewer_id;
		Show_view_text_timer -= FrameTime;

		viewer_id = "";
		switch( Viewer->type )
		{
			case OBJ_FIREBALL:	viewer_name = "Fireball"; break;
			case OBJ_ROBOT:		viewer_name = "Robot";
#ifdef EDITOR
										viewer_id = Robot_names[Viewer->id];
#endif
				break;
			case OBJ_HOSTAGE:		viewer_name = "Hostage"; break;
			case OBJ_PLAYER:		viewer_name = "Player"; break;
			case OBJ_WEAPON:		viewer_name = "Weapon"; break;
			case OBJ_CAMERA:		viewer_name = "Camera"; break;
			case OBJ_POWERUP:		viewer_name = "Powerup";
#ifdef EDITOR
										viewer_id = Powerup_names[Viewer->id];
#endif
				break;
			case OBJ_DEBRIS:		viewer_name = "Debris"; break;
			case OBJ_CNTRLCEN:	viewer_name = "Reactor"; break;
			default:					viewer_name = "Unknown"; break;
		}

		switch ( Viewer->control_type) {
			case CT_NONE:			control_name = "Stopped"; break;
			case CT_AI:				control_name = "AI"; break;
			case CT_FLYING:		control_name = "Flying"; break;
			case CT_SLEW:			control_name = "Slew"; break;
			case CT_FLYTHROUGH:	control_name = "Flythrough"; break;
			case CT_MORPH:			control_name = "Morphing"; break;
			default:					control_name = "Unknown"; break;
		}

		gr_set_curfont(GAME_FONT);
		gr_set_fontcolor(BM_XRGB(31,0,0),-1);
		gr_printf( 0x8000, (SHEIGHT/10), "%li: %s [%s] View - %s",Viewer-Objects, viewer_name, viewer_id, control_name );

	}
}
#endif

void render_countdown_gauge()
{
	if (!Endlevel_sequence && Control_center_destroyed  && (Countdown_seconds_left>-1)) { // && (Countdown_seconds_left<127))	{

		if (!is_D2_OEM && !is_MAC_SHARE && !is_SHAREWARE)    // no countdown on registered only
		{
			//	On last level, we don't want a countdown.
			if (PLAYING_BUILTIN_MISSION && Current_level_num == Last_level)
			{
				if (!(Game_mode & GM_MULTI))
					return;
				if (Game_mode & GM_MULTI_ROBOTS)
					return;
			}
		}

		gr_set_curfont(GAME_FONT);
		gr_set_fontcolor(BM_XRGB(0,63,0),-1);
		gr_printf(0x8000, (LINE_SPACING*6)+FSPACY(1), "T-%d s", Countdown_seconds_left );
	}
}

void game_draw_hud_stuff()
{
#ifndef NDEBUG
	draw_window_label();
#endif

#ifdef NETWORK
	game_draw_multi_message();
#endif

	game_draw_marker_message();

	if ((Newdemo_state == ND_STATE_PLAYBACK) || (Newdemo_state == ND_STATE_RECORDING)) {
		char message[128];
		int y;

		if (Newdemo_state == ND_STATE_PLAYBACK) {
			if (Newdemo_show_percentage) {
			  	sprintf(message, "%s (%d%%%% %s)", TXT_DEMO_PLAYBACK, newdemo_get_percent_done(), TXT_DONE);
			} else {
				sprintf (message, " ");
			}
		} else {
			extern int Newdemo_num_written;
			sprintf (message, "%s (%dK)", TXT_DEMO_RECORDING, (Newdemo_num_written / 1024));
		}

		gr_set_curfont( GAME_FONT );
		gr_set_fontcolor( BM_XRGB(27,0,0), -1 );

		y = GHEIGHT-(LINE_SPACING*2);

		if (PlayerCfg.CockpitMode[1] == CM_FULL_COCKPIT)
			y = grd_curcanv->cv_bitmap.bm_h / 1.2 ;
		if (PlayerCfg.CockpitMode[1] != CM_REAR_VIEW)
			gr_string(0x8000, y, message );
	}

	render_countdown_gauge();

	if (GameCfg.FPSIndicator && PlayerCfg.CockpitMode[1] != CM_REAR_VIEW)
		show_framerate();

	if (Newdemo_state == ND_STATE_PLAYBACK)
		Game_mode = Newdemo_game_mode;

	draw_hud();

	if (Newdemo_state == ND_STATE_PLAYBACK)
		Game_mode = GM_NORMAL;

	if ( Player_is_dead )
		player_dead_message();
}

extern int gr_bitblt_dest_step_shift;
extern int gr_bitblt_double;

#if 0
void expand_row(ubyte * dest, ubyte * src, int num_src_pixels );
#pragma aux expand_row parm [edi] [esi] [ecx] modify exact [ecx esi edi eax ebx] = \
	"add	esi, ecx"			\
	"dec	esi"					\
	"add	edi, ecx"			\
	"add	edi, ecx"			\
	"dec	edi"					\
	"dec	edi"					\
"nextpixel:"					\
	"mov	al,[esi]"			\
	"mov	ah, al"				\
	"dec	esi"					\
	"mov	[edi], ax"			\
	"dec	edi"					\
	"dec	edi"					\
	"dec	ecx"					\
	"jnz	nextpixel"			\
"done:"
#else
void expand_row(ubyte * dest, ubyte * src, int num_src_pixels )
{
	int i;
	
	for (i = 0; i < num_src_pixels; i++) {
		*dest++ = *src;
		*dest++ = *src++;
	}
}
#endif

// doubles the size in x or y of a bitmap in place.
void game_expand_bitmap( grs_bitmap * bmp, uint flags )
{
	int i;
	ubyte * dptr, * sptr;

	switch(flags & 3)	{
	case 2:	// expand x
		Assert( bmp->bm_rowsize == bmp->bm_w*2 );
		dptr = &bmp->bm_data[(bmp->bm_h-1)*bmp->bm_rowsize];
		for (i=bmp->bm_h-1; i>=0; i-- )	{
			expand_row( dptr, dptr, bmp->bm_w );	
			dptr -= bmp->bm_rowsize;
		}
		bmp->bm_w *= 2;
		break;
	case 1:	// expand y
		dptr = &bmp->bm_data[(2*(bmp->bm_h-1)+1)*bmp->bm_rowsize];
		sptr = &bmp->bm_data[(bmp->bm_h-1)*bmp->bm_rowsize];
		for (i=bmp->bm_h-1; i>=0; i-- )	{
			memcpy( dptr, sptr, bmp->bm_w );	
			dptr -= bmp->bm_rowsize;
			memcpy( dptr, sptr, bmp->bm_w );	
			dptr -= bmp->bm_rowsize;
			sptr -= bmp->bm_rowsize;
		}
		bmp->bm_h *= 2;
		break;
	case 3:	// expand x & y
		Assert( bmp->bm_rowsize == bmp->bm_w*2 );
		dptr = &bmp->bm_data[(2*(bmp->bm_h-1)+1)*bmp->bm_rowsize];
		sptr = &bmp->bm_data[(bmp->bm_h-1)*bmp->bm_rowsize];
		for (i=bmp->bm_h-1; i>=0; i-- )	{
			expand_row( dptr, sptr, bmp->bm_w );	
			dptr -= bmp->bm_rowsize;
			expand_row( dptr, sptr, bmp->bm_w );	
			dptr -= bmp->bm_rowsize;
			sptr -= bmp->bm_rowsize;
		}
		bmp->bm_w *= 2;
		bmp->bm_h *= 2;
		break;
	}
}

extern int SW_drawn[2], SW_x[2], SW_y[2], SW_w[2], SW_h[2];
ubyte RenderingType=0;
ubyte DemoDoingRight=0,DemoDoingLeft=0;
extern ubyte DemoDoRight,DemoDoLeft;
extern object DemoRightExtra,DemoLeftExtra;

char DemoWBUType[]={0,WBU_GUIDED,WBU_MISSILE,WBU_REAR,WBU_ESCORT,WBU_MARKER,0};
char DemoRearCheck[]={0,0,0,1,0,0,0};
static const char *const DemoExtraMessage[]={"PLAYER","GUIDED","MISSILE","REAR","GUIDE-BOT","MARKER","SHIP"};

void show_extra_views()
{
	int did_missile_view=0;
	int save_newdemo_state = Newdemo_state;
	int w;

	if (Newdemo_state==ND_STATE_PLAYBACK)
	{
		if (DemoDoLeft)
		{
			DemoDoingLeft=DemoDoLeft;

			if (DemoDoLeft==3)
				do_cockpit_window_view(0,ConsoleObject,1,WBU_REAR,"REAR");
			else
				do_cockpit_window_view(0,&DemoLeftExtra,DemoRearCheck[DemoDoLeft],DemoWBUType[DemoDoLeft],DemoExtraMessage[DemoDoLeft]);
		}
		else
			do_cockpit_window_view(0,NULL,0,WBU_WEAPON,NULL);
	
		if (DemoDoRight)
		{
			DemoDoingRight=DemoDoRight;
			
			if (DemoDoRight==3)
				do_cockpit_window_view(1,ConsoleObject,1,WBU_REAR,"REAR");
			else
			{
				do_cockpit_window_view(1,&DemoRightExtra,DemoRearCheck[DemoDoRight],DemoWBUType[DemoDoRight],DemoExtraMessage[DemoDoRight]);
			}
		}
		else
			do_cockpit_window_view(1,NULL,0,WBU_WEAPON,NULL);
		
		DemoDoLeft=DemoDoRight=0;
		DemoDoingLeft=DemoDoingRight=0;
		return;
	}

	if (Guided_missile[Player_num] && Guided_missile[Player_num]->type==OBJ_WEAPON && Guided_missile[Player_num]->id==GUIDEDMISS_ID && Guided_missile[Player_num]->signature==Guided_missile_sig[Player_num]) 
	{
		if (PlayerCfg.GuidedInBigWindow)
		{
			RenderingType=6+(1<<4);
			do_cockpit_window_view(1,Viewer,0,WBU_MISSILE,"SHIP");
		}
		else
		{
			RenderingType=1+(1<<4);
			do_cockpit_window_view(1,Guided_missile[Player_num],0,WBU_GUIDED,"GUIDED");
		}
			
		did_missile_view=1;
	}
	else {

		if (Guided_missile[Player_num]) {		//used to be active
			if (!PlayerCfg.GuidedInBigWindow)
				do_cockpit_window_view(1,NULL,0,WBU_STATIC,NULL);
			Guided_missile[Player_num] = NULL;
		}

		if (Missile_viewer) //do missile view
		{
			if (Missile_viewer_sig == -1)
				Missile_viewer_sig = Missile_viewer->signature;
			if (PlayerCfg.MissileViewEnabled && Missile_viewer->type!=OBJ_NONE && Missile_viewer->signature == Missile_viewer_sig) {
  				RenderingType=2+(1<<4);
				do_cockpit_window_view(1,Missile_viewer,0,WBU_MISSILE,"MISSILE");
				did_missile_view=1;
			}
			else {
				Missile_viewer = NULL;
				Missile_viewer_sig = -1;
				RenderingType=255;
				do_cockpit_window_view(1,NULL,0,WBU_STATIC,NULL);
			}
		}
	}

	for (w=0;w<2;w++) {

		if (w==1 && did_missile_view)
			continue;		//if showing missile view in right window, can't show anything else

		//show special views if selected
		switch (PlayerCfg.Cockpit3DView[w]) {
			case CV_NONE:
				RenderingType=255;
				do_cockpit_window_view(w,NULL,0,WBU_WEAPON,NULL);
				break;
			case CV_REAR:
				if (Rear_view) {		//if big window is rear view, show front here
					RenderingType=3+(w<<4);				
					do_cockpit_window_view(w,ConsoleObject,0,WBU_REAR,"FRONT");
				}
				else {					//show normal rear view
					RenderingType=3+(w<<4);				
					do_cockpit_window_view(w,ConsoleObject,1,WBU_REAR,"REAR");
				}
			 	break;
			case CV_ESCORT: {
				object *buddy;
				buddy = find_escort();
				if (buddy == NULL) {
					do_cockpit_window_view(w,NULL,0,WBU_WEAPON,NULL);
					PlayerCfg.Cockpit3DView[w] = CV_NONE;
				}
				else {
					RenderingType=4+(w<<4);
					do_cockpit_window_view(w,buddy,0,WBU_ESCORT,PlayerCfg.GuidebotName);
				}
				break;
			}
#ifdef NETWORK
			case CV_COOP: {
				int player = Coop_view_player[w];

	         RenderingType=255; // don't handle coop stuff			
				
				if (player!=-1 && Players[player].connected && ((Game_mode & GM_MULTI_COOP) || ((Game_mode & GM_TEAM) && (get_team(player) == get_team(Player_num)))))
					do_cockpit_window_view(w,&Objects[Players[Coop_view_player[w]].objnum],0,WBU_COOP,Players[Coop_view_player[w]].callsign);
				else {
					do_cockpit_window_view(w,NULL,0,WBU_WEAPON,NULL);
					PlayerCfg.Cockpit3DView[w] = CV_NONE;
				}
				break;
			}
#endif
			case CV_MARKER: {
				char label[10];
				RenderingType=5+(w<<4);
				if (Marker_viewer_num[w] == -1 || MarkerObject[Marker_viewer_num[w]] == -1) {
					PlayerCfg.Cockpit3DView[w] = CV_NONE;
					break;
				}
				sprintf(label,"Marker %d",Marker_viewer_num[w]+1);
				do_cockpit_window_view(w,&Objects[MarkerObject[Marker_viewer_num[w]]],0,WBU_MARKER,label);
				break;
			}
			default:
				Int3();		//invalid window type
		}
	}
	RenderingType=0;
	Newdemo_state = save_newdemo_state;
}

int BigWindowSwitch=0;
extern int force_cockpit_redraw;
void update_cockpits();

//render a frame for the game
void game_render_frame_mono(int flip)
{
	int no_draw_hud=0;

	gr_set_current_canvas(&Screen_3d_window);
	
	if (Guided_missile[Player_num] && Guided_missile[Player_num]->type==OBJ_WEAPON && Guided_missile[Player_num]->id==GUIDEDMISS_ID && Guided_missile[Player_num]->signature==Guided_missile_sig[Player_num] && PlayerCfg.GuidedInBigWindow) {
		object *viewer_save = Viewer;

		if (PlayerCfg.CockpitMode[1]==CM_FULL_COCKPIT || PlayerCfg.CockpitMode[1]==CM_REAR_VIEW)
		{
			 BigWindowSwitch=1;
			 force_cockpit_redraw=1;
			 PlayerCfg.CockpitMode[1]=CM_STATUS_BAR;
			 return;
		}

		Viewer = Guided_missile[Player_num];

		update_rendered_data(0, Viewer, 0, 0);
		render_frame(0, 0);

		wake_up_rendered_objects(Viewer, 0);
		show_HUD_names();

		Viewer = viewer_save;

		gr_set_curfont( GAME_FONT );
		gr_set_fontcolor( BM_XRGB(27,0,0), -1 );

		gr_printf(0x8000, FSPACY(1), "Guided Missile View");

		show_reticle(RET_TYPE_CROSS_V1, 0);

		HUD_render_message_frame();

		no_draw_hud=1;
	}
	else
	{
		if (BigWindowSwitch)
		{
			force_cockpit_redraw=1;
			PlayerCfg.CockpitMode[1]=(Rear_view?CM_REAR_VIEW:CM_FULL_COCKPIT);
			BigWindowSwitch=0;
			return;
		}
		update_rendered_data(0, Viewer, Rear_view, 0);
		render_frame(0, 0);
	}

	gr_set_current_canvas(&Screen_3d_window);

	update_cockpits();

	if (Newdemo_state == ND_STATE_PLAYBACK)
		Game_mode = Newdemo_game_mode;

	if (PlayerCfg.CockpitMode[1]==CM_FULL_COCKPIT || PlayerCfg.CockpitMode[1]==CM_STATUS_BAR)
		render_gauges();

	if (Newdemo_state == ND_STATE_PLAYBACK)
		Game_mode = GM_NORMAL;

	gr_set_current_canvas(&Screen_3d_window);
	if (!no_draw_hud)
		game_draw_hud_stuff();

	gr_set_current_canvas(NULL);

	show_extra_views();		//missile view, buddy bot, etc.

#ifdef NETWORK
	if (netplayerinfo_on && Game_mode & GM_MULTI)
		show_netplayerinfo();
#endif
}

void toggle_cockpit()
{
	int new_mode=CM_FULL_SCREEN;

	if (Rear_view || Player_is_dead)
		return;

	switch (PlayerCfg.CockpitMode[1])
	{
		case CM_FULL_COCKPIT:
			new_mode = CM_STATUS_BAR;
			break;
		case CM_STATUS_BAR:
			new_mode = CM_FULL_SCREEN;
			break;
		case CM_FULL_SCREEN:
			new_mode = CM_FULL_COCKPIT;
			break;
	}

	select_cockpit(new_mode);
	HUD_clear_messages();
	PlayerCfg.CockpitMode[0] = new_mode;
	write_player_file();
}

int last_drawn_cockpit = -1;
extern void ogl_loadbmtexture(grs_bitmap *bm);

// This actually renders the new cockpit onto the screen.
void update_cockpits()
{
	grs_bitmap *bm;

	PIGGY_PAGE_IN(cockpit_bitmap[PlayerCfg.CockpitMode[1]+(HIRESMODE?(Num_cockpits/2):0)]);
	bm=&GameBitmaps[cockpit_bitmap[PlayerCfg.CockpitMode[1]+(HIRESMODE?(Num_cockpits/2):0)].index];

	switch( PlayerCfg.CockpitMode[1] )	{
		case CM_FULL_COCKPIT:
			gr_set_current_canvas(NULL);
#ifdef OGL
			ogl_ubitmapm_cs (0, 0, -1, -1, bm, 255, F1_0);
#else
			gr_ubitmapm(0,0, bm);
#endif
			break;
		case CM_REAR_VIEW:
			gr_set_current_canvas(NULL);
#ifdef OGL
			ogl_ubitmapm_cs (0, 0, -1, -1, bm, 255, F1_0);
#else
			gr_ubitmapm(0,0, bm);
#endif
			break;
	
		case CM_FULL_SCREEN:
			break;
	
		case CM_STATUS_BAR:
	
			gr_set_current_canvas(NULL);
#ifdef OGL
			ogl_ubitmapm_cs (0, (HIRESMODE?(SHEIGHT*2)/2.6:(SHEIGHT*2)/2.72), -1, ((int) ((double) (bm->bm_h) * (HIRESMODE?(double)SHEIGHT/480:(double)SHEIGHT/200) + 0.5)), bm,255, F1_0);
#else
			gr_ubitmapm(0,SHEIGHT-bm->bm_h,bm);
#endif
			break;
	
		case CM_LETTERBOX:
			gr_set_current_canvas(NULL);
			break;

	}

	gr_set_current_canvas(NULL);

	if (PlayerCfg.CockpitMode[1] != last_drawn_cockpit)
		last_drawn_cockpit = PlayerCfg.CockpitMode[1];
	else
		return;

	if (PlayerCfg.CockpitMode[1]==CM_FULL_COCKPIT || PlayerCfg.CockpitMode[1]==CM_STATUS_BAR)
		init_gauges();

}

void game_render_frame()
{
	set_screen_mode( SCREEN_GAME );
	play_homing_warning();
	game_render_frame_mono(GameArg.DbgUseDoubleBuffer);
}

//show a message in a nice little box
void show_boxed_message(char *msg, int RenderFlag)
{
	int w,h,aw;
	int x,y;
	
	gr_set_current_canvas(NULL);
	gr_set_curfont( MEDIUM1_FONT );
	gr_set_fontcolor(BM_XRGB(31, 31, 31), -1);
	gr_get_string_size(msg,&w,&h,&aw);
	
	x = (SWIDTH-w)/2;
	y = (SHEIGHT-h)/2;
	
	nm_draw_background(x-BORDERX,y-BORDERY,x+w+BORDERX,y+h+BORDERY);
	
	gr_string( 0x8000, y, msg );
	
	// If we haven't drawn behind it, need to flip
	if (!RenderFlag)
		gr_flip();
}
