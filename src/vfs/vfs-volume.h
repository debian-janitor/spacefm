/*
*  C Interface: vfs-volume
*
*
* Copyright: See COPYING file that comes with this distribution
*
*/

#ifndef _VFS_VOLUME_H_
#define _VFS_VOLUME_H_

#include <glib.h>
#include "settings.h"

G_BEGIN_DECLS

typedef struct _VFSVolume VFSVolume;

typedef enum{
    VFS_VOLUME_ADDED,
    VFS_VOLUME_REMOVED,
    VFS_VOLUME_MOUNTED, /* Not implemented */
    VFS_VOLUME_UNMOUNTED, /* Not implemented */
    VFS_VOLUME_EJECT,
    VFS_VOLUME_CHANGED
}VFSVolumeState;

typedef void ( *VFSVolumeCallback ) ( VFSVolume* vol,
                                      VFSVolumeState state,
                                      gpointer user_data );

gboolean vfs_volume_init();

gboolean vfs_volume_finalize();

const GList* vfs_volume_get_all_volumes();

void vfs_volume_add_callback( VFSVolumeCallback cb, gpointer user_data );

void vfs_volume_remove_callback( VFSVolumeCallback cb, gpointer user_data );

gboolean vfs_volume_mount( VFSVolume* vol, GError** err );

gboolean vfs_volume_umount( VFSVolume *vol, GError** err );

gboolean vfs_volume_eject( VFSVolume *vol, GError** err );

const char* vfs_volume_get_disp_name( VFSVolume *vol );

const char* vfs_volume_get_mount_point( VFSVolume *vol );

const char* vfs_volume_get_device( VFSVolume *vol );

const char* vfs_volume_get_fstype( VFSVolume *vol );

const char* vfs_volume_get_icon( VFSVolume *vol );

gboolean vfs_volume_is_removable( VFSVolume *vol );

gboolean vfs_volume_is_mounted( VFSVolume *vol );

gboolean vfs_volume_requires_eject( VFSVolume *vol );

#ifdef HAVE_HAL
gboolean vfs_volume_mount_by_udi( const char* udi, GError** err );

gboolean vfs_volume_umount_by_udi( const char* udi, GError** err );

gboolean vfs_volume_eject_by_udi( const char* udi, GError** err );

#else

enum{
    DEVICE_TYPE_BLOCK,
    DEVICE_TYPE_NETWORK
};

struct _VFSVolume
{
    int device_type;
    char* device_file;
    char* udi;
    char* disp_name;
    char* icon;
    char* mount_point;
    gboolean is_mounted : 1;
    /* gboolean is_hotpluggable : 1; */
    gboolean is_removable : 1;
    gboolean is_mountable : 1;
    gboolean is_audiocd : 1;
    gboolean is_dvd : 1;
    gboolean is_blank : 1;
    gboolean requires_eject : 1;
    gboolean is_user_visible : 1;
    gboolean nopolicy : 1;
    gboolean is_optical : 1;
    gboolean is_floppy : 1;
    gboolean is_table : 1;
    gboolean ever_mounted : 1;
    gboolean inhibit_auto : 1;
    time_t automount_time;
    gpointer open_main_window;
    guint64 size;
    char* label;
    char* fs_type;
};

typedef struct netmount_t {
    char* url;
    char* fstype;
    char* host;
    char* ip;
    char* port;
    char* user;
    char* pass;
    char* path;
} netmount_t;

gboolean vfs_volume_command( char* command, char** output );
char* vfs_volume_get_mount_command( VFSVolume* vol, char* default_options );
char* vfs_volume_get_mount_options( VFSVolume* vol, char* options );
void vfs_volume_automount( VFSVolume* vol );
void vfs_volume_set_info( VFSVolume* volume );
char* vfs_volume_device_mount_cmd( const char* device_file, const char* options );
char* vfs_volume_device_unmount_cmd( const char* device_file );
char* vfs_volume_device_info( const char* device_file );
int parse_network_url( const char* url, const char* fstype,
                                                        netmount_t** netmount );
void vfs_volume_special_mounted( const char* device_file );
gboolean vfs_volume_dir_avoid_changes( const char* dir );
dev_t get_device_parent( dev_t dev );

#endif

G_END_DECLS

#endif
