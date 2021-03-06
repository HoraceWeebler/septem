/**
* configuration defines for the mud
* Holds configuration data and other constants.
*/
#pragma once
#ifndef CONFIG_H
#define CONFIG_H

/**
* Should we reverse-lookup connections?
*/
#define RDNS

/**
* The mud default telnet port.
*/
#define DEFAULT_PORT 9999

/**
* The backlog used for listen()
*/
#define LISTEN_BACKLOG 5

#define DEFAULT_GAME_DATA_PATH "/home/ken/git-repos/septem/game_data/"

#define DEFAULT_SOL_INIT_PATH DEFAULT_GAME_DATA_PATH "init"

#define DEFAULT_ENTITIES_PATH DEFAULT_GAME_DATA_PATH "entities/"

#define DEFAULT_PLAYER_ENTITY_SCRIPT DEFAULT_ENTITIES_PATH "player"

#define DEFAULT_COMMANDS_PATH DEFAULT_GAME_DATA_PATH "cmds/"

#define DEFAULT_DAEMON_PATH DEFAULT_GAME_DATA_PATH "daemon/"

#define DEFAULT_REALMS_PATH DEFAULT_GAME_DATA_PATH "realms/"

#define DEFAULT_VOID_PATH DEFAULT_REALMS_PATH "void"



#define DEFAULT_LOG_PATH DEFAULT_GAME_DATA_PATH "logs/"

#define DEFAULT_ACCOUNT_PATH DEFAULT_GAME_DATA_PATH "accounts/"

#define DEFAULT_CHARS_PATH DEFAULT_GAME_DATA_PATH "characters/"

//#define DEFAULT_GAME_DATA_PATH "vfs" /* This is the root directory for the virtual file system */
#define DEFAULT_ACCOUNT_FILE_EXT ".xml"

#define DEFAULT_SERVER_CONTACT_EMAIL_ADDRESS "caliel@septemmud.com"

/**
* How many pulses will be ran per second?
* Make sure this is divisible evenly.
* For example, 1000/10, 1000/2, etc.
* Change this if you need faster pulses, but understand that it will give slower updates eventually.
*/
#define PULSES_PER_SECOND 10
#define MS_PER_PULSE 1000/PULSES_PER_SECOND

/**
* Should we write log messages to console?
*/
#define LOG_CONSOLE

/**
* Max size, in bytes of the log.
*/
#define LOG_MAXSIZE 1024*1024
/**
* Max amount of files to keep from rotating log.
*/
#define LOG_MAXFILES 10 //maximum number of logs to keep.
/**
* Minimum log level to write to the console.
*/
#define MIN_LOG_LEVEL (LOG_LEVEL)WARN

/**
* The name of the mud.
*/
#define MUD_NAME "Se7en"

/**
* The maximum number of history entries each channel will keep.
*/
#define MAX_CHAN_HISTORY_LENGTH 20 //the maximum number of entries channels will log.

/**
* The maximum amount of time in seconds a player can idle before getting kicked.
*/
#define GAME_IDLE_TIME (60*60)
/**
* The maximum amount of time in seconds a player will be able to idle at login.
*/
#define LOGIN_IDLE_TIME 30
/**
* the maximum amount of time in seconds a player can be linkdead before being logged out.
*/
#define LINKDEATH_TIME (60*10)

/**
*Comment this out if you want all scripting functions enabled by default.
* Leaving it commented will remove functions like Player::SetPassword from being exposed to scripting.
*/
#define SCRIPT_SECURE

/**
* Determines whether or not callouts should be profiled.
*/
#define PROFILE_CALLOUTS

/**
* Pulse living every x seconds.
*/
#define LIVING_PULSE 2
/**
* Pulse world every x seconds.
*/
#define WORLD_PULSE 60

/**
* How frequently to save players.
*/
#define SAVE_INTERVAL (60*5)
/**
* Amount of time before backing up the player's files.
*/
#define BACKUP_INTERVAL (60*30)

//Defines for locating files:
////#define MOTD_FILE "../txt/motd" //message of the day shown after login
////#define LOGIN_FILE "../txt/welcome" //banner shown at login
////#define COPYOVER_FILE "../copyover.dat" //stores player connection info
////#define BIN_FILE "../bin/aspen" //used for copyovers.
////#define EVENT_FILE "../logs/events.log" //our main log file
////#define EVENT_NAME "events" //the actual name of the event log.
////#define SCRIPT_FILE "../logs/script.log" //the name of the scripting log file.
////#define SCRIPT_NAME "script"
////#define HELP_FILE "../data/help.dat"
////#define SOCIALS_FILE "../data/socials.dat"

//directories:
////#define PLAYER_DIR "../data/players/"
////#define STATE_DIR "../data/state/"
////#define BACKUP_DIR "../data/backups/"
////#define AREA_DIR "../data/areas/"
////#define AREA_STARTFILE "../data/areas/start"

/**
* VNums can be stored to keep track of unused numbers.
* this makes it quicker to allocate static objects and rooms.
* If memory is a concern (multiple zones, etc) consider reducing this if you do not have frequent use of allocations
* Which would require the search for a free VNUM.
* @todo add the ability to refill at a certain level (so 50% of capacity).
*/
#define VNUMKEEP 100

/**
* Maximum password length.
*/
#define MAX_PASSWORD 20
/**
* Minimum password length.
*/
#define MIN_PASSWORD 5

#define MAX_PASSWORD_RETRY 5

#define NEW_LINE_CHAR 0x0D
/**
* @todo remove these checks.
* These modules (with the exception of scripting and possibly help ) are required.
*/
#define MODULE_SCRIPTING
#define MODULE_SYSLOG
#define MODULE_HELP
#define OLC

/**
* Leave this commented if you would like initialization to check for files and create them upon launch.
* Only useful for first-time launch.
*/
//#define NO_INIT_DEFAULTS

/**
* How many bytes to allocate for MCCP buffers for individual sockets.
* Do not change unless you have a good reason.
*/
#define MCCP_BUFFER_SIZE 4096


#endif
