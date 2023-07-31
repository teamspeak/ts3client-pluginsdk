#ifndef PUBLIC_ERRORS_H
#define PUBLIC_ERRORS_H

//The idea here is: the values are 2 bytes wide, the first byte identifies the group, the second the count within that group

enum Ts3ErrorType {
    //general
    ERROR_ok                     = 0x0000, ///< Indicates success.
    ERROR_undefined              = 0x0001,
    ERROR_not_implemented        = 0x0002, ///< The attempted operation is not available in this context
    ERROR_ok_no_update           = 0x0003, ///< Indicates success, but no change occurred. Returned for example upon flushing (e.g. using \ref ts3client_flushChannelUpdates) when all indicated changes already matched the current state.
    ERROR_dont_notify            = 0x0004,
    ERROR_lib_time_limit_reached = 0x0005,
    ERROR_out_of_memory          = 0x0006, ///< Not enough system memory to perform operation
    ERROR_canceled               = 0x0007,

    //dunno
    ERROR_command_not_found           = 0x0100,
    ERROR_unable_to_bind_network_port = 0x0101, ///< Unspecified failure to create a listening port
    ERROR_no_network_port_available   = 0x0102, ///< Failure to initialize a listening port for FileTransfer
    ERROR_port_already_in_use         = 0x0103, ///< Specified port is already in use by a different application

    //client
    ERROR_client_invalid_id                  = 0x0200, ///< Client no longer connected
    ERROR_client_nickname_inuse              = 0x0201, ///< Client name is already in use. Client names must be unique
    ERROR_client_protocol_limit_reached      = 0x0203, ///< Too many clients on the server
    ERROR_client_invalid_type                = 0x0204, ///< Function called for normal clients that is only available for query clients or vice versa
    ERROR_client_already_subscribed          = 0x0205, ///< Attempting to subscribe to a channel already subscribed to
    ERROR_client_not_logged_in               = 0x0206,
    ERROR_client_could_not_validate_identity = 0x0207, ///< Identity not valid or insufficient security level
    ERROR_client_invalid_password            = 0x0208,
    ERROR_client_version_outdated            = 0x020a, ///< Server requires newer client version as determined by the min_client_version properties
    ERROR_client_is_flooding                 = 0x020c, ///< Triggered flood protection. Further information is supplied in the extra message if applicable.
    ERROR_client_hacked                      = 0x020d,
    ERROR_client_cannot_verify_now           = 0x020e,
    ERROR_client_login_not_permitted         = 0x020f,
    ERROR_client_not_subscribed              = 0x0210, ///< Action is only available on subscribed channels

    //channel
    ERROR_channel_invalid_id                = 0x0300, ///< Channel does not exist on the server (any longer)
    ERROR_channel_protocol_limit_reached    = 0x0301, ///< Too many channels on the server
    ERROR_channel_already_in                = 0x0302, ///< Attempting to move a client or channel to its current channel
    ERROR_channel_name_inuse                = 0x0303, ///< Channel name is already taken by another channel. Channel names must be unique
    ERROR_channel_not_empty                 = 0x0304, ///< Attempting to delete a channel with clients or sub channels in it
    ERROR_channel_can_not_delete_default    = 0x0305, ///< Default channel cannot be deleted. Set a new default channel first (see \ref ts3client_setChannelVariableAsInt or \ref ts3server_setChannelVariableAsInt )
    ERROR_channel_default_require_permanent = 0x0306, ///< Attempt to set a non permanent channel as default channel. Set channel to permanent first (see \ref ts3client_setChannelVariableAsInt or \ref ts3server_setChannelVariableAsInt )
    ERROR_channel_invalid_flags             = 0x0307, ///< Invalid combination of \ref ChannelProperties, trying to remove \ref CHANNEL_FLAG_DEFAULT or set a password on the default channel
    ERROR_channel_parent_not_permanent      = 0x0308, ///< Attempt to move a permanent channel into a non-permanent one, or set a channel to be permanent that is a sub channel of a non-permanent one
    ERROR_channel_maxclients_reached        = 0x0309, ///< Channel is full as determined by its \ref CHANNEL_MAXCLIENTS setting
    ERROR_channel_maxfamily_reached         = 0x030a, ///< Channel tree is full as determined by its \ref CHANNEL_MAXFAMILYCLIENTS setting
    ERROR_channel_invalid_order             = 0x030b, ///< Invalid value for the \ref CHANNEL_ORDER property. The specified channel must exist on the server and be on the same level.
    ERROR_channel_no_filetransfer_supported = 0x030c, ///< Invalid \ref CHANNEL_FILEPATH set for the channel
    ERROR_channel_invalid_password          = 0x030d, ///< Channel has a password not matching the password supplied in the call
    // used in public_rare_errors                = 0x030e,
    ERROR_channel_invalid_security_hash = 0x030f,

    //server
    ERROR_server_invalid_id         = 0x0400, ///< Chosen virtual server does not exist or is offline
    ERROR_server_running            = 0x0401, ///< attempting to delete a server that is running. Stop the server before deleting it.
    ERROR_server_is_shutting_down   = 0x0402, ///< Client disconnected because the server is going offline
    ERROR_server_maxclients_reached = 0x0403, ///< Given in the onConnectStatusChange event when the server has reached its maximum number of clients as defined by the \ref VIRTUALSERVER_MAXCLIENTS property
    ERROR_server_invalid_password   = 0x0404, ///< Specified server password is wrong. Provide the correct password in the \ref ts3client_startConnection / \ref ts3client_startConnectionWithChannelID call.
    ERROR_server_is_virtual         = 0x0407, ///< Server is in virtual status. The attempted action is not possible in this state. Start the virtual server first.
    ERROR_server_is_not_running     = 0x0409, ///< Attempting to stop a server that is not online.
    ERROR_server_is_booting         = 0x040a, // Not used
    ERROR_server_status_invalid     = 0x040b,
    ERROR_server_version_outdated   = 0x040d, ///< Attempt to connect to an outdated server version. The server needs to be updated.
    ERROR_server_duplicate_running  = 0x040e, ///< This server is already running within the instance. Each virtual server may only exist once.

    //parameter
    ERROR_parameter_quote         = 0x0600, // Not used
    ERROR_parameter_invalid_count = 0x0601, ///< Attempt to flush changes without previously calling set*VariableAs* since the last flush
    ERROR_parameter_invalid       = 0x0602, ///< At least one of the supplied parameters did not meet the criteria for that parameter
    ERROR_parameter_not_found     = 0x0603, ///< Failure to supply all the necessary parameters
    ERROR_parameter_convert       = 0x0604, ///< Invalid type supplied for a parameter, such as passing a string (ie. "five") that expects a number.
    ERROR_parameter_invalid_size  = 0x0605, ///< Value out of allowed range. Such as strings are too long/short or numeric values outside allowed range
    ERROR_parameter_missing       = 0x0606, ///< Neglecting to specify a required parameter
    ERROR_parameter_checksum      = 0x0607, ///< Attempting to deploy a modified snapshot

    //unsorted, need further investigation
    ERROR_vs_critical                          = 0x0700, ///< Failure to create default channel
    ERROR_connection_lost                      = 0x0701, ///< Generic error with the connection.
    ERROR_not_connected                        = 0x0702, ///< Attempting to call functions with a serverConnectionHandler that is not connected. You can use \ref ts3client_getConnectionStatus to check whether the connection handler is connected to a server
    ERROR_no_cached_connection_info            = 0x0703, ///< Attempting to query connection information (bandwidth usage, ping, etc) without requesting them first using \ref ts3client_requestConnectionInfo
    ERROR_currently_not_possible               = 0x0704, ///< Requested information is not currently available. You may have to call \ref ts3client_requestClientVariables or \ref ts3client_requestServerVariables
    ERROR_failed_connection_initialisation     = 0x0705, ///< No TeamSpeak server running on the specified IP address and port
    ERROR_could_not_resolve_hostname           = 0x0706, ///< Failure to resolve the specified hostname to an IP address
    ERROR_invalid_server_connection_handler_id = 0x0707, ///< Attempting to perform actions on a non-existent server connection handler
    ERROR_could_not_initialise_input_manager   = 0x0708, // Not used
    ERROR_clientlibrary_not_initialised        = 0x0709, ///< Calling client library functions without successfully calling \ref ts3client_initClientLib before
    ERROR_serverlibrary_not_initialised        = 0x070a, ///< Calling server library functions without successfully calling \ref ts3server_initServerLib before
    ERROR_whisper_too_many_targets             = 0x070b, ///< Using a whisper list that contain more clients than the servers \ref VIRTUALSERVER_MIN_CLIENTS_IN_CHANNEL_BEFORE_FORCED_SILENCE property
    ERROR_whisper_no_targets                   = 0x070c, ///< The active whisper list is empty or no clients matched the whisper list (e.g. all channels in the list are empty)
    ERROR_connection_ip_protocol_missing       = 0x070d, ///< Invalid or unsupported protocol (e.g. attempting an IPv6 connection on an IPv4 only machine)
    ERROR_handshake_failed                     = 0x070e,
    ERROR_illegal_server_license               = 0x070f,

    //file transfer
    ERROR_file_invalid_name                     = 0x0800, ///< Invalid UTF8 string or not a valid file
    ERROR_file_invalid_permissions              = 0x0801, ///< Permissions prevent opening the file
    ERROR_file_already_exists                   = 0x0802, ///< Target path already exists as a directory
    ERROR_file_not_found                        = 0x0803, ///< Attempt to access or move non existing file
    ERROR_file_io_error                         = 0x0804, ///< Generic file input / output error
    ERROR_file_invalid_transfer_id              = 0x0805, ///< Attempt to get information about a file transfer after it has already been cleaned up. File transfer information is not available indefinitely after the transfer completed
    ERROR_file_invalid_path                     = 0x0806, ///< specified path contains invalid characters or does not start with "/"
    ERROR_file_no_files_available               = 0x0807, // Not used
    ERROR_file_overwrite_excludes_resume        = 0x0808, ///< File overwrite and resume are mutually exclusive. Only one or neither can be 1.
    ERROR_file_invalid_size                     = 0x0809, ///< Attempt to write more bytes than claimed file size.
    ERROR_file_already_in_use                   = 0x080a, ///< File is currently not available, try again later.
    ERROR_file_could_not_open_connection        = 0x080b, ///< Generic failure in file transfer connection / other party did not conform to file transfer protocol
    ERROR_file_no_space_left_on_device          = 0x080c, ///< Operating system reports hard disk is full. May be caused by quota limitations.
    ERROR_file_exceeds_file_system_maximum_size = 0x080d, ///< File is too large for the file system of the target device.
    ERROR_file_transfer_connection_timeout      = 0x080e, // Not used
    ERROR_file_connection_lost                  = 0x080f, ///< File input / output timeout or connection failure
    ERROR_file_exceeds_supplied_size            = 0x0810, // Not used
    ERROR_file_transfer_complete                = 0x0811, ///< Indicates successful completion
    ERROR_file_transfer_canceled                = 0x0812, ///< Transfer was cancelled through @ref ts3client_haltTransfer
    ERROR_file_transfer_interrupted             = 0x0813, ///< Transfer failed because the server is shutting down, or network connection issues
    ERROR_file_transfer_server_quota_exceeded   = 0x0814, ///< Transfer terminated due to server bandwidth quota being exceeded. No client can transfer files.
    ERROR_file_transfer_client_quota_exceeded   = 0x0815, ///< Attempt to transfer more data than allowed by this clients' bandwidth quota. Other clients may continue to transfer files.
    ERROR_file_transfer_reset                   = 0x0816, // Not used
    ERROR_file_transfer_limit_reached           = 0x0817, ///< Too many file transfers are in progress. Try again later
    ERROR_file_invalid_storage_class            = 0x0818, // TODO: Invalid storage class for HTTP FileTransfer (what is a storage class?)
    ERROR_file_invalid_dimension                = 0x0819, ///< Avatar image exceeds maximum width or height accepted by the server.
    ERROR_file_transfer_channel_quota_exceeded  = 0x081a, ///< Transfer failed because the channel quota was exceeded. Uploading to this channel is not possible, but other channels may be fine.

    //sound
    ERROR_sound_preprocessor_disabled          = 0x0900, ///< Cannot set or query pre processor variables with preprocessing disabled
    ERROR_sound_internal_preprocessor          = 0x0901,
    ERROR_sound_internal_encoder               = 0x0902,
    ERROR_sound_internal_playback              = 0x0903,
    ERROR_sound_no_capture_device_available    = 0x0904, ///< No audio capture devices are available
    ERROR_sound_no_playback_device_available   = 0x0905, ///< No audio playback devices are available
    ERROR_sound_could_not_open_capture_device  = 0x0906, ///< Error accessing audio device, or audio device does not support the requested mode
    ERROR_sound_could_not_open_playback_device = 0x0907, ///< Error accessing audio device, or audio device does not support the requested mode
    ERROR_sound_handler_has_device     = 0x0908, ///< Attempt to open a sound device on a connection handler which already has an open device. Close the already open device first using \ref ts3client_closeCaptureDevice or \ref ts3client_closePlaybackDevice
    ERROR_sound_invalid_capture_device = 0x0909, ///< Attempt to use a device for capture that does not support capturing audio
    ERROR_sound_invalid_playback_device    = 0x090a, ///< Attempt to use a device for playback that does not support playback of audio
    ERROR_sound_invalid_wave               = 0x090b, ///< Attempt to use a non WAV file in \ref ts3client_playWaveFile or \ref ts3client_playWaveFileHandle
    ERROR_sound_unsupported_wave           = 0x090c, ///< Unsupported wave file used in \ref ts3client_playWaveFile or \ref ts3client_playWaveFileHandle.
    ERROR_sound_open_wave                  = 0x090d, ///< Failure to open the specified sound file
    ERROR_sound_internal_capture           = 0x090e,
    ERROR_sound_device_in_use              = 0x090f, ///< Attempt to unregister a custom device that is being used. Close the device first using \ref ts3client_closeCaptureDevice or \ref ts3client_closePlaybackDevice
    ERROR_sound_device_already_registerred = 0x0910, ///< Attempt to register a custom device with a device id that has already been used in a previous call. Device ids must be unique.
    ERROR_sound_unknown_device             = 0x0911, ///< Attempt to open, close, unregister or use a device which is not known. Custom devices must be registered before being used (see \ref ts3client_registerCustomDevice)
    ERROR_sound_unsupported_frequency      = 0x0912,
    ERROR_sound_invalid_channel_count      = 0x0913, ///< Invalid device audio channel count, must be > 0
    ERROR_sound_read_wave                  = 0x0914, ///< Failure to read sound samples from an opened wave file. Is this a valid wave file?
    ERROR_sound_need_more_data             = 0x0915, // for internal purposes only
    ERROR_sound_device_busy                = 0x0916, // for internal purposes only
    ERROR_sound_no_data                    = 0x0917, ///< Indicates there is currently no data for playback, e.g. nobody is speaking right now.
    ERROR_sound_channel_mask_mismatch      = 0x0918, ///< Opening a device with an unsupported channel count

    //permissions
    ERROR_permissions_client_insufficient = 0x0a08, ///< Not enough permissions to perform the requested activity
    ERROR_permissions                     = 0x0a0c, ///< Permissions to use sound device not granted by operating system, e.g. Windows denied microphone access.

    //accounting
    ERROR_accounting_virtualserver_limit_reached = 0x0b00, ///< Attempt to use more virtual servers than allowed by the license
    ERROR_accounting_slot_limit_reached          = 0x0b01, ///< Attempt to set more slots than allowed by the license
    ERROR_accounting_license_file_not_found      = 0x0b02, // Not used
    ERROR_accounting_license_date_not_ok         = 0x0b03, ///< License expired or not valid yet
    ERROR_accounting_unable_to_connect_to_server = 0x0b04, ///< Failure to communicate with accounting backend
    ERROR_accounting_unknown_error               = 0x0b05, ///< Failure to write update license file
    ERROR_accounting_server_error                = 0x0b06, // Not used
    ERROR_accounting_instance_limit_reached      = 0x0b07, ///< More than one process of the server is running
    ERROR_accounting_instance_check_error        = 0x0b08, ///< Shared memory access failure.
    ERROR_accounting_license_file_invalid        = 0x0b09, ///< License is not a TeamSpeak license
    ERROR_accounting_running_elsewhere           = 0x0b0a, ///< A copy of this server is already running in another instance. Each server may only exist once.
    ERROR_accounting_instance_duplicated         = 0x0b0b, ///< A copy of this server is running already in this process. Each server may only exist once.
    ERROR_accounting_already_started             = 0x0b0c, ///< Attempt to start a server that is already running
    ERROR_accounting_not_started                 = 0x0b0d,
    ERROR_accounting_to_many_starts              = 0x0b0e, ///< Starting instance / virtual servers too often in too short a time period

    //provisioning server
    /// @cond HAS_PROVISIONING
    ERROR_provisioning_invalid_password          = 0x1100,
    ERROR_provisioning_invalid_request           = 0x1101,
    ERROR_provisioning_no_slots_available        = 0x1102,
    ERROR_provisioning_pool_missing              = 0x1103,
    ERROR_provisioning_pool_unknown              = 0x1104,
    ERROR_provisioning_unknown_ip_location       = 0x1105,
    ERROR_provisioning_internal_tries_exceeded   = 0x1106,
    ERROR_provisioning_too_many_slots_requested  = 0x1107,
    ERROR_provisioning_too_many_reserved         = 0x1108,
    ERROR_provisioning_could_not_connect         = 0x1109,
    ERROR_provisioning_auth_server_not_connected = 0x1110,
    ERROR_provisioning_auth_data_too_large       = 0x1111,
    ERROR_provisioning_already_initialized       = 0x1112,
    ERROR_provisioning_not_initialized           = 0x1113,
    ERROR_provisioning_connecting                = 0x1114,
    ERROR_provisioning_already_connected         = 0x1115,
    ERROR_provisioning_not_connected             = 0x1116,
    ERROR_provisioning_io_error                  = 0x1117,
    ERROR_provisioning_invalid_timeout           = 0x1118,
    ERROR_provisioning_ts3server_not_found       = 0x1119,
    ERROR_provisioning_no_permission             = 0x111A,
    /// @endcond
};
#endif
