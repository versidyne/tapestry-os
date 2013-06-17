// cli.h -- Defines input / output routines.
//          File Version: 1.1

#ifndef CLI_H
#define CLI_H

#include "../core/info.h"
#include "../core/cpu.h"
#include "../drivers/monitor.h"
#include "../drivers/mouse.h"
#include "../drivers/pit.h"
#include "../drivers/sound.h"
#include "../drivers/vga.h"
#include "../vfs/fs.h"
#include "../lib/stdio.h"

// Creates a command line interface.
void cl_interface(fs_node_t *fs_root);

// Handles a command issued by the user.
void cl_handler(char* buffer, fs_node_t *fs_root);

// Displays all files in the file system.
void dir_disp(fs_node_t *fs_root);

// Displays all files in the file system and their contents.
void file_disp(fs_node_t *fs_root);

// Tests a forking iteration.
void fork_disp();

// Displays the help menu on the main screen.
void help_disp();

// Displays the logo on the main screen.
void logo_disp();

// Display time on the main screen.
void time_disp();

// Tests a usermode iteration.
void umode_disp(fs_node_t *fs_root);

// Runs a usermode cli
void ucl_interface(fs_node_t *fs_root);

// Displays the system version on the main screen.
void version_disp();

#endif // CLI_H
