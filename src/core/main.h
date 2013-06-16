// main.h -- Defines all main interface usage.
//           File Version: 1.0

#ifndef MAIN_H
#define MAIN_H

#include "common.h"

#include "multiboot.h"
#include "cpu.h"
#include "../drivers/monitor.h"
#include "../drivers/mouse.h"
#include "../drivers/pit.h"
#include "../mm/descriptor_tables.h"
#include "../mm/paging.h"
#include "../lib/syscall.h"
#include "../proc/task.h"
#include "../ui/cli.h"
#include "../vfs/fs.h"
#include "../vfs/initrd.h"

#endif // MAIN_H
