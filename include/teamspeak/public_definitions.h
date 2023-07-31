#ifndef PUBLIC_DEFINITIONS_H
#define PUBLIC_DEFINITIONS_H

#include "teamlog/logtypes.h"

#define TS3_MAX_SIZE_CHANNEL_NAME 40       // channel name maximum length in characters
#define TS3_MAX_SIZE_VIRTUALSERVER_NAME 64 // virtual server name maximum length in characters
#define TS3_MAX_SIZE_CLIENT_NICKNAME 64    // client display name length limit in characters
#define TS3_MIN_SIZE_CLIENT_NICKNAME 3     // client display name minimum length in characters
#define TS3_MAX_SIZE_REASON_MESSAGE 80     // length limit in characters for kick, move, etc reasons

#define TS3_MAX_SIZE_TEXTMESSAGE 8192         // text message length limit, measured in bytes (utf8 encoded)
#define TS3_MAX_SIZE_CHANNEL_TOPIC 255        // channel topic lengt limith, measured in bytes (utf8 encoded)
#define TS3_MAX_SIZE_CHANNEL_DESCRIPTION 8192 // channel description length limit, measured in bytes (utf8 encoded)
// server welcome message length limit measured in bytes (utf8 encoded)
#define TS3_MAX_SIZE_VIRTUALSERVER_WELCOMEMESSAGE 1024
#define TS3_SIZE_MYTSID 44
// minimum amount of seconds before a clientID that was in use can be assigned to a new client
#define TS3_MIN_SECONDS_CLIENTID_REUSE 300

#if defined(WIN32) || defined(__WIN32__) || defined(_WIN32)
typedef unsigned __int16 anyID;
typedef unsigned __int64 uint64;
#ifndef EXPORTDLL
#ifdef BUILDING_DLL
#define EXPORTDLL __declspec(dllexport)
#else
#define EXPORTDLL
#endif
#endif
#else
#include <stdint.h>
typedef uint16_t anyID;
typedef uint64_t uint64;
#ifndef EXPORTDLL
#ifdef BUILDING_DLL
#define EXPORTDLL __attribute__((visibility("default")))
#else
#define EXPORTDLL
#endif
#endif
#endif

enum Visibility {
    ENTER_VISIBILITY = 0, ///< Client joined from an unsubscribed channel, or joined the server.
    RETAIN_VISIBILITY,    ///< Client switched from one subscribed channel to a different subscribed channel.
    LEAVE_VISIBILITY      ///< Client switches to an unsubscribed channel, or disconnected from server.
};

enum ConnectStatus {
    STATUS_DISCONNECTED = 0,        ///< There is no activity to the server, this is the default value
    STATUS_CONNECTING,              ///< We are trying to connect, we haven't got a client id yet, we haven't been accepted by the server
    STATUS_CONNECTED,               ///< The server has accepted us, we can talk and hear and we have a client id, but we don't
                                    ///< have the channels and clients yet, we can get server infos (welcome msg etc.)
    STATUS_CONNECTION_ESTABLISHING, ///< we are connected and we are visible
    STATUS_CONNECTION_ESTABLISHED,  ///< we are connected and we have the client and channels available
};

enum LocalTestMode { TEST_MODE_OFF = 0, TEST_MODE_VOICE_LOCAL_ONLY, TEST_MODE_VOICE_LOCAL_AND_REMOTE, TEST_MODE_TALK_STATUS_CHANGES_ONLY };

enum TalkStatus {
    STATUS_NOT_TALKING            = 0, ///< client is not talking
    STATUS_TALKING                = 1, ///< client is talking
    STATUS_TALKING_WHILE_DISABLED = 2, ///< client is talking while the microphone is muted (only valid for own client)
};

enum CodecType {
    CODEC_SPEEX_NARROWBAND = 0, ///< (deprecated) mono,   16bit,  8kHz, bitrate dependent on the quality setting
    CODEC_SPEEX_WIDEBAND,       ///< (deprecated) mono,   16bit, 16kHz, bitrate dependent on the quality setting
    CODEC_SPEEX_ULTRAWIDEBAND,  ///< (deprecated) mono,   16bit, 32kHz, bitrate dependent on the quality setting
    CODEC_CELT_MONO,            ///< (deprecated) mono,   16bit, 48kHz, bitrate dependent on the quality setting
    CODEC_OPUS_VOICE,           ///< mono,   16bit, 48khz, bitrate dependent on the quality setting, optimized for voice
    CODEC_OPUS_MUSIC,           ///< stereo, 16bit, 48khz, bitrate dependent on the quality setting, optimized for music
};

enum CodecEncryptionMode {
    CODEC_ENCRYPTION_PER_CHANNEL = 0, ///< voice data encryption decided per channel
    CODEC_ENCRYPTION_FORCED_OFF,      ///< voice data encryption disabled
    CODEC_ENCRYPTION_FORCED_ON,       ///< voice data encryption enabled
};

enum TextMessageTargetMode {
    TextMessageTarget_CLIENT = 1, ///< Message is a private message to another client
    TextMessageTarget_CHANNEL,    ///< Message is sent to a channel, received by all clients in that channel at the time
    TextMessageTarget_SERVER,     ///< Message is sent to every client on the server
    TextMessageTarget_MAX
};

enum MuteInputStatus {
    MUTEINPUT_NONE = 0, ///< Microphone is not muted, audio is sent to the server
    MUTEINPUT_MUTED,    ///< Microphone is muted, no audio is transmitted to the server
};

enum MuteOutputStatus {
    MUTEOUTPUT_NONE = 0, ///< Speaker is active, server is sending us audio
    MUTEOUTPUT_MUTED,    ///< Speaker is muted, server is not sending audio to us
};

enum HardwareInputStatus {
    HARDWAREINPUT_DISABLED = 0, ///< no capture device opened
    HARDWAREINPUT_ENABLED,      ///< capture device open
};

enum HardwareOutputStatus {
    HARDWAREOUTPUT_DISABLED = 0, ///< no playback device opened
    HARDWAREOUTPUT_ENABLED,      ///< playback device open
};

enum InputDeactivationStatus {
    INPUT_ACTIVE      = 0, ///< Audio is captured from the capture device.
    INPUT_DEACTIVATED = 1, ///< No audio is captured from the capture device.
};

enum ReasonIdentifier {
    REASON_NONE                             = 0,  ///< no reason data
    REASON_MOVED                            = 1,  ///< client was moved
    REASON_SUBSCRIPTION                     = 2,  // no reason data
    REASON_LOST_CONNECTION                  = 3,  // reasonmsg=reason
    REASON_KICK_CHANNEL                     = 4,  //{SectionInvoker} reasonmsg=reason               //{SectionInvoker} is only added server->client
    REASON_KICK_SERVER                      = 5,  //{SectionInvoker} reasonmsg=reason               //{SectionInvoker} is only added server->client
    REASON_KICK_SERVER_BAN                  = 6,  //{SectionInvoker} reasonmsg=reason bantime=time  //{SectionInvoker} is only added server->client
    REASON_SERVERSTOP                       = 7,  // reasonmsg=reason
    REASON_CLIENTDISCONNECT                 = 8,  // reasonmsg=reason
    REASON_CHANNELUPDATE                    = 9,  // no reason data
    REASON_CHANNELEDIT                      = 10, //{SectionInvoker}
    REASON_CLIENTDISCONNECT_SERVER_SHUTDOWN = 11, // reasonmsg=reason
};

enum Protocol_Encryption_Cipher { AES_128 = 0, AES_256, PROTOCOL_ENCRYPTION_CIPHER_END_MARKER };

enum ChannelProperties {
    CHANNEL_NAME = 0,             ///< String.  Read/Write. Name of the channel. Always available.
    CHANNEL_TOPIC,                ///< String.  Read/Write. Short single line text describing what the channel is about. Always available.
    CHANNEL_DESCRIPTION,          ///< String.  Read/Write. Arbitrary text (up to 8k bytes) with information about the channel.
                                  ///< Must be requested (\ref ts3client_requestChannelDescription)
    CHANNEL_PASSWORD,             ///< String.  Read/Write. Password of the channel. Read access is limited to the server. Clients
                                  ///< will only ever see the last password they attempted to use when joining the channel. Always available.
    CHANNEL_CODEC,                ///< Integer. Read/Write. The codec this channel is using. One of the values from the \ref CodecType
                                  ///< enum. Always available.
    CHANNEL_CODEC_QUALITY,        ///< Integer. Read/Write. The quality setting of the channel. Valid values are 0 to 10 inclusive.
                                  ///< Higher value means better voice quality but also more bandwidth usage. Always available.
    CHANNEL_MAXCLIENTS,           ///< Integer. Read/Write. The number of clients that can be in the channel simultaneously.
                                  ///< Always available.
    CHANNEL_MAXFAMILYCLIENTS,     ///< Integer. Read/Write. The total number of clients that can be in this channel and all
                                  ///< sub channels of this channel. Always available.
    CHANNEL_ORDER,                ///< UInt64.  Read/Write. The ID of the channel below which this channel should be displayed. If 0
                                  ///< the channel is sorted at the top of the current level. Always available.
    CHANNEL_FLAG_PERMANENT,       ///< Integer. Read/Write. Boolean (1/0) indicating whether the channel remains when empty.
                                  ///< Permanent channels are stored to the database and available after server restart. SDK
                                  ///< users will need to take care of restoring channel at server start on their own.
                                  ///< Mutually exclusive with \ref CHANNEL_FLAG_SEMI_PERMANENT. Always available.
    CHANNEL_FLAG_SEMI_PERMANENT,  ///< Integer. Read/Write. Boolean (1/0) indicating whether the channel remains when
                                  ///< empty. Semi permanent channels are not stored to disk and gone after server
                                  ///< restart but remain while empty. Mutually exclusive with \ref
                                  ///< CHANNEL_FLAG_PERMANENT. Always available.
    CHANNEL_FLAG_DEFAULT,         ///< Integer. Read/Write. Boolean (1/0). The default channel is the channel that all clients
                                  ///< are located in when they join the server, unless the client explicitly specified a
                                  ///< different channel when connecting and is allowed to join their preferred channel. Only
                                  ///< one channel on the server can have this flag set. The default channel must have \ref
                                  ///< CHANNEL_FLAG_PERMANENT set. Always available.
    CHANNEL_FLAG_PASSWORD,        ///< Integer. Read/Write. Boolean (1/0) indicating whether this channel is password protected.
                                  ///< When removing or setting \ref CHANNEL_PASSWORD you also need to adjust this flag.
    CHANNEL_CODEC_LATENCY_FACTOR, ///< (deprecated) Integer. Read/Write. Allows to increase packet size, reducing
                                  ///< bandwith at the cost of higher latency of voice transmission. Valid values are
                                  ///< 1-10 inclusive. 1 is the default and offers the lowest latency. Always available.
    CHANNEL_CODEC_IS_UNENCRYPTED, ///< Integer. Read/Write. Boolean (1/0). If 0 voice data is encrypted, if 1 the voice
                                  ///< data is not encrypted. Only used if the server \ref
                                  ///< VIRTUALSERVER_CODEC_ENCRYPTION_MODE is set to \ref CODEC_ENCRYPTION_PER_CHANNEL.
                                  ///< Always available.
    CHANNEL_SECURITY_SALT,        ///< String.  Read/Write. SDK Only, not used by TeamSpeak. This channels security hash. When
                                  ///< a client joins their \ref CLIENT_SECURITY_HASH is compared to this value, to allow or
                                  ///< deny the client access to the channel. Used to enforce clients joining the server with
                                  ///< specific identity and \ref CLIENT_META_DATA. See SDK Documentation about this feature
                                  ///< for further details. Always available.
    CHANNEL_DELETE_DELAY,         ///< UInt64.  Read/Write. Number of seconds deletion of temporary channels is delayed after
                                  ///< the last client leaves the channel. Channel is only deleted if empty when the delete
                                  ///< delay expired. Always available.
    CHANNEL_UNIQUE_IDENTIFIER,    ///< String.  Read only.  An identifier that uniquely identifies a channel. Available in
                                  ///< Server >= 3.10.0
    CHANNEL_ENDMARKER,
};

enum ClientProperties {
    CLIENT_UNIQUE_IDENTIFIER = 0,    ///< String.  Read only.  Public Identity, can be used to identify a client
                                     ///< installation. Remains identical as long as the client keeps using the same
                                     ///< identity. Available for visible clients.
    CLIENT_NICKNAME,                 ///< String.  Read/Write. Display name of the client. Available for visible clients.
    CLIENT_VERSION,                  ///< String.  Read only.  Version String of the client used. For clients other than ourself this
                                     ///< needs to be requested (\ref ts3client_requestClientVariables).
    CLIENT_PLATFORM,                 ///< String.  Read only.  Operating system used by the client. For other clients other than ourself
                                     ///< this needs to be requested (\ref ts3client_requestClientVariables).
    CLIENT_FLAG_TALKING,             ///< Integer. Read only.  Whether the client is talking. Available on clients that are either
                                     ///< whispering to us, or in our channel.
    CLIENT_INPUT_MUTED,              ///< Integer. Read/Write. Microphone mute status. Available for visible clients. One of the
                                     ///< values from the \ref MuteInputStatus enum.
    CLIENT_OUTPUT_MUTED,             ///< Integer. Read only.  Speaker mute status. Speaker mute implies microphone mute. Available
                                     ///< for visible clients. One of the values from the \ref MuteOutputStatus enum.
    CLIENT_OUTPUTONLY_MUTED,         ///< Integer. Read only.  Speaker mute status. Microphone may be active. Available for
                                     ///< visible clients. One of the values from the \ref MuteOutputStatus enum.
    CLIENT_INPUT_HARDWARE,           ///< Integer. Read only.  Indicates whether a capture device is open. Available for visible
                                     ///< clients. One of the values from the \ref HardwareInputStatus enum.
    CLIENT_OUTPUT_HARDWARE,          ///< Integer. Read only.  Indicates whether a playback device is open. Available for visible
                                     ///< clients. One of the values from the \ref HardwareOutputStatus enum.
    CLIENT_INPUT_DEACTIVATED,        ///< Integer. Read/Write. Not available server side. Local microphone mute status.
                                     ///< Available only for own client. Used to implement Push To Talk. One of the values from
                                     ///< the \ref InputDeactivationStatus enum.
    CLIENT_IDLE_TIME,                ///< UInt64.  Read only.  Seconds since last activity. Available only for own client.
    CLIENT_DEFAULT_CHANNEL,          ///< String.  Read only.  User specified channel they joined when connecting to the server.
                                     ///< Available only for own client.
    CLIENT_DEFAULT_CHANNEL_PASSWORD, ///< String.  Read only.  User specified channel password for the channel they
                                     ///< attempted to join when connecting to the server. Available only for own
                                     ///< client.
    CLIENT_SERVER_PASSWORD,          ///< String.  Read only.  User specified server password. Available only for own client.
    CLIENT_META_DATA,                ///< String.  Read/Write. Can be used to store up to 4096 bytes of information on clients. Not
                                     ///< used by TeamSpeak. Available for visible clients.
    CLIENT_IS_MUTED,                 ///< Integer. Read only.  Not available server side. Indicates whether we have muted the client
                                     ///< using \ref ts3client_requestMuteClients. Available for visible clients other than ourselves.
    CLIENT_IS_RECORDING,             ///< Integer. Read only.  Indicates whether the client is recording incoming audio. Available
                                     ///< for visible clients.
    CLIENT_VOLUME_MODIFICATOR,       ///< Integer. Read only.  Volume adjustment for this client as set by \ref
                                     ///< ts3client_setClientVolumeModifier. Available for visible clients.
    CLIENT_VERSION_SIGN,             ///< String.  Read only.  TeamSpeak internal signature.
    CLIENT_SECURITY_HASH,            ///< String.  Read/Write. This clients security hash. Not used by TeamSpeak, SDK only. Hash is
                                     ///< provided by an outside source. A channel will use the security salt + other client data
                                     ///< to calculate a hash, which must be the same as the one provided here. See SDK
                                     ///< documentation about Client / Channel Security Hashes for more details.
    CLIENT_ENCRYPTION_CIPHERS,       ///< String.  Read only.  SDK only. List of available ciphers this client can use.
    CLIENT_ENDMARKER,
};

enum VirtualServerProperties {
    VIRTUALSERVER_UNIQUE_IDENTIFIER = 0, ///< String.  Read only.  Unique identifier for a virtual server, does not
                                         ///< change on server restart. Available if \ref ts3client_getConnectionStatus
                                         ///< is >= \ref STATUS_CONNECTED.
    VIRTUALSERVER_NAME,                  ///< String.  Read/Write. The virtual server display name. Available if \ref
                                         ///< ts3client_getConnectionStatus is >= \ref STATUS_CONNECTED.
    VIRTUALSERVER_WELCOMEMESSAGE,        ///< String.  Read/Write. The welcome message displayed to clients on connect.
                                         ///< Available if \ref ts3client_getConnectionStatus is >= \ref STATUS_CONNECTED. Not
                                         ///< updated automatically when changed, updates need to be requested (\ref
                                         ///< ts3client_requestServerVariables).
    VIRTUALSERVER_PLATFORM,              ///< String.  Read only.  The operating system the server is running on. Available if \ref
                                         ///< ts3client_getConnectionStatus is >= \ref STATUS_CONNECTED.
    VIRTUALSERVER_VERSION,               ///< String.  Read only.  The server software version string. Available if \ref
                                         ///< ts3client_getConnectionStatus is >= \ref STATUS_CONNECTED.
    VIRTUALSERVER_MAXCLIENTS,            ///< UInt64.  Read/Write. The maximum number of clients that can be connected
                                         ///< simultaneously. Only available on request (\ref ts3client_requestServerVariables).
    VIRTUALSERVER_PASSWORD,              ///< String.  Read/Write. The server password. Read access is limited to the server. Clients
                                         ///< will only get the password they supplied when connecting. Available if \ref
                                         ///< ts3client_getConnectionStatus is >= \ref STATUS_CONNECTED.
    VIRTUALSERVER_CLIENTS_ONLINE,        ///< UInt64.  Read only.  The current number of clients connected to the server,
                                         ///< including query connections. Only available on request (\ref
                                         ///< ts3client_requestServerVariables).
    VIRTUALSERVER_CHANNELS_ONLINE,       ///< UInt64.  Read only.  The current number of channels on the server. Only
                                         ///< available on request (\ref ts3client_requestServerVariables).
    VIRTUALSERVER_CREATED,               ///< Integer. Read only.  The time this virtual server was created as unix timestamp.
                                         ///< Available if \ref ts3client_getConnectionStatus is >= \ref STATUS_CONNECTED.
    VIRTUALSERVER_UPTIME,                ///< UInt64.  Read only.  Number of seconds that have passed since the virtual server was
                                         ///< started. Only available on request (\ref ts3client_requestServerVariables).
    VIRTUALSERVER_CODEC_ENCRYPTION_MODE, ///< Integer. Read/Write. Boolean (1/0) that specifies if voice data is encrypted
                                         ///< during transfer. One of the values from the \ref CodecEncryptionMode enum.
                                         ///< Available if \ref ts3client_getConnectionStatus is >= \ref STATUS_CONNECTED.
    VIRTUALSERVER_ENCRYPTION_CIPHERS,    ///< String.  Read/Write. Comma separated list of available ciphers to encrypt the
                                         ///< connection. The server will use the first cipher in the list that is also
                                         ///< listed in the \ref CLIENT_ENCRYPTION_CIPHERS of the connecting client.
                                         ///< Clients will fail to connect if no match is found. Always available.
    VIRTUALSERVER_ENDMARKER,
    VIRTUALSERVER_FILEBASE = 24,                     ///< String.  Read only.  The path to the base directory used to store files
                                                     ///< transferred using file transfer. Available only on the server. Is set by \ref
                                                     ///< ts3server_enableFileManager
    VIRTUALSERVER_MAX_DOWNLOAD_TOTAL_BANDWIDTH = 29, ///< UInt64.  Read/Write. Maximum traffic in bytes the server can
                                                     ///< use for file transfer downloads. Only available on request
                                                     ///< (\ref ts3client_requestServerVariables).
    VIRTUALSERVER_MAX_UPLOAD_TOTAL_BANDWIDTH = 30,   ///< UInt64.  Read/Write. Maximum traffic in bytes the server can use
                                                     ///< for file transfer uploads. Only available on request (=>
                                                     ///< requestServerVariables)
    VIRTUALSERVER_LOG_FILETRANSFER = 64              ///< Integer. Read/Write. Boolean (1/0) indicating whether to include file
                                                     ///< transfer activities (uploading or downloading of files) in the server log.
                                                     ///< Always available.
};

/**
 * Various connection properties.
 * These are all read only, and except for your own client must be requested using \ref ts3client_requestConnectionInfo
 */
enum ConnectionProperties {
    CONNECTION_PING = 0,                                 ///< UInt64. Round trip latency for the connection based on the last 5 seconds. On the server
                                                         ///< this is the average across all connected clients for the last 5 seconds.
    CONNECTION_PING_DEVIATION,                           ///< Double. Standard deviation for the round trip latency in \ref CONNECTION_PING
    CONNECTION_CONNECTED_TIME,                           ///< UInt64. Seconds the client has been connected.
    CONNECTION_IDLE_TIME,                                ///< UInt64. Time in seconds since the last activity (voice transmission, switching channels,
                                                         ///< changing mic / speaker mute status) of the client.
    CONNECTION_CLIENT_IP,                                ///< String. IP of this client (as seen from the server side)
    CONNECTION_CLIENT_PORT,                              ///< UInt64. Client side port of this client (as seen from the server side)
    CONNECTION_SERVER_IP,                                ///< String. The IP or hostname used to connect to the server. Only available on yourself.
    CONNECTION_SERVER_PORT,                              ///< UInt64. The server port connected to. Only available on yourself.
    CONNECTION_PACKETS_SENT_SPEECH,                      ///< UInt64. The number of voice packets transmitted by the client.
    CONNECTION_PACKETS_SENT_KEEPALIVE,                   ///< UInt64. The number of keep alive packets transmitted by the client.
    CONNECTION_PACKETS_SENT_CONTROL,                     ///< UInt64. The number of command & control packets transmitted by the client.
    CONNECTION_PACKETS_SENT_TOTAL,                       ///< UInt64. Total number of packets transmitted by the client. Equal to the sum of
                                                         ///< \ref CONNECTION_PACKETS_SENT_SPEECH, \ref CONNECTION_PACKETS_SENT_KEEPALIVE and
                                                         ///< \ref CONNECTION_PACKETS_SENT_CONTROL
    CONNECTION_BYTES_SENT_SPEECH,                        ///< UInt64. Outgoing traffic used for voice data by the client.
    CONNECTION_BYTES_SENT_KEEPALIVE,                     ///< UInt64. Outgoing traffic used for keeping the connection alive by the client.
    CONNECTION_BYTES_SENT_CONTROL,                       ///< UInt64. Outgoing traffic used for command & control data by the client.
    CONNECTION_BYTES_SENT_TOTAL,                         ///< UInt64. Total outgoing traffic to the server by this client. Equal to the sum of
                                                         ///< \ref CONNECTION_BYTES_SENT_SPEECH, \ref CONNECTION_BYTES_SENT_KEEPALIVE and \ref
                                                         ///< CONNECTION_BYTES_SENT_CONTROL
    CONNECTION_PACKETS_RECEIVED_SPEECH,                  ///< UInt64. Number of voice packets received by the client.
    CONNECTION_PACKETS_RECEIVED_KEEPALIVE,               ///< UInt64. Number of keep alive packets received by the client.
    CONNECTION_PACKETS_RECEIVED_CONTROL,                 ///< UInt64. Number of command & control packets received by the client.
    CONNECTION_PACKETS_RECEIVED_TOTAL,                   ///< UInt64. Total number of packets received by the client. Equal to the sum of
                                                         ///< \ref CONNECTION_PACKETS_RECEIVED_SPEECH, \ref
                                                         ///< CONNECTION_PACKETS_RECEIVED_KEEPALIVE and \ref
                                                         ///< CONNECTION_PACKETS_RECEIVED_CONTROL
    CONNECTION_BYTES_RECEIVED_SPEECH,                    ///< UInt64. Incoming traffic used by the client for voice data.
    CONNECTION_BYTES_RECEIVED_KEEPALIVE,                 ///< UInt64. Incoming traffic used by the client to keep the connection alive.
    CONNECTION_BYTES_RECEIVED_CONTROL,                   ///< UInt64. Incoming traffic used by the client for command & control data.
    CONNECTION_BYTES_RECEIVED_TOTAL,                     ///< UInt64. Total incoming traffic used by the client. Equal to the sum of \ref
                                                         ///< CONNECTION_BYTES_RECEIVED_SPEECH, \ref CONNECTION_BYTES_RECEIVED_KEEPALIVE and
                                                         ///< \ref CONNECTION_BYTES_RECEIVED_CONTROL
    CONNECTION_PACKETLOSS_SPEECH,                        ///< Double. Percentage points of voice packets for the client that did not arrive at
                                                         ///< the client or server averaged across the last 5 seconds.
    CONNECTION_PACKETLOSS_KEEPALIVE,                     ///< Double. Percentage points of keep alive packets for the client that did not
                                                         ///< arrive at the client or server averaged across the last 5 seconds.
    CONNECTION_PACKETLOSS_CONTROL,                       ///< Double. Percentage points of command & control packets for the client that did
                                                         ///< not arrive at the client or server averaged across the last 5 seconds.
    CONNECTION_PACKETLOSS_TOTAL,                         ///< Double. Cumulative chance in percentage points with which a packet round trip
                                                         ///< failed because a packet was lost
    CONNECTION_SERVER2CLIENT_PACKETLOSS_SPEECH,          ///< Double. Probability with which a voice packet sent by the server
                                                         ///< was not received by the client.
    CONNECTION_SERVER2CLIENT_PACKETLOSS_KEEPALIVE,       ///< Double. Probability with which a keepalive packet sent by the
                                                         ///< server was not received by the client.
    CONNECTION_SERVER2CLIENT_PACKETLOSS_CONTROL,         ///< Double. Probability with which a control packet sent by the server
                                                         ///< was not received by the client.
    CONNECTION_SERVER2CLIENT_PACKETLOSS_TOTAL,           ///< Double. Probability with which a packet sent by the server was not
                                                         ///< received by the client.
    CONNECTION_CLIENT2SERVER_PACKETLOSS_SPEECH,          ///< Double. Probability with which a speech packet sent by the client
                                                         ///< was not received by the server.
    CONNECTION_CLIENT2SERVER_PACKETLOSS_KEEPALIVE,       ///< Double. Probability with which a keepalive packet sent by the
                                                         ///< client was not received by the server.
    CONNECTION_CLIENT2SERVER_PACKETLOSS_CONTROL,         ///< Double. Probability with which a control packet sent by the client
                                                         ///< was not received by the server.
    CONNECTION_CLIENT2SERVER_PACKETLOSS_TOTAL,           ///< Double. Probability with which a packet sent by the client was not
                                                         ///< received by the server.
    CONNECTION_BANDWIDTH_SENT_LAST_SECOND_SPEECH,        ///< UInt64. Number of bytes sent for speech data in the last second.
    CONNECTION_BANDWIDTH_SENT_LAST_SECOND_KEEPALIVE,     ///< UInt64. Number of bytes sent for keepalive data in the last second.
    CONNECTION_BANDWIDTH_SENT_LAST_SECOND_CONTROL,       ///< UInt64. Number of bytes sent for control data in the last second.
    CONNECTION_BANDWIDTH_SENT_LAST_SECOND_TOTAL,         ///< UInt64. Number of bytes sent in the last second.
    CONNECTION_BANDWIDTH_SENT_LAST_MINUTE_SPEECH,        ///< UInt64. Bytes per second sent for speech data, averaged over the
                                                         ///< last minute.
    CONNECTION_BANDWIDTH_SENT_LAST_MINUTE_KEEPALIVE,     ///< UInt64. Bytes per second sent for keepalive data, averaged
                                                         ///< over the last minute.
    CONNECTION_BANDWIDTH_SENT_LAST_MINUTE_CONTROL,       ///< UInt64. Bytes per second sent for control data, averaged over
                                                         ///< the last minute.
    CONNECTION_BANDWIDTH_SENT_LAST_MINUTE_TOTAL,         ///< UInt64. Bytes per second sent, averaged over the last minute.
    CONNECTION_BANDWIDTH_RECEIVED_LAST_SECOND_SPEECH,    ///< UInt64. Number of bytes received for speech data in the last second.
    CONNECTION_BANDWIDTH_RECEIVED_LAST_SECOND_KEEPALIVE, ///< UInt64. Number of bytes received for keepalive data in the
                                                         ///< last second.
    CONNECTION_BANDWIDTH_RECEIVED_LAST_SECOND_CONTROL,   ///< UInt64. Number of bytes received for control data in the
                                                         ///< last second.
    CONNECTION_BANDWIDTH_RECEIVED_LAST_SECOND_TOTAL,     ///< UInt64. Number of bytes received in the last second.
    CONNECTION_BANDWIDTH_RECEIVED_LAST_MINUTE_SPEECH,    ///< UInt64. Bytes per second received for speech data, averaged
                                                         ///< over the last minute.
    CONNECTION_BANDWIDTH_RECEIVED_LAST_MINUTE_KEEPALIVE, ///< UInt64. Bytes per second received for keepalive data,
                                                         ///< averaged over the last minute.
    CONNECTION_BANDWIDTH_RECEIVED_LAST_MINUTE_CONTROL,   ///< UInt64. Bytes per second received for control data, averaged
                                                         ///< over the last minute.
    CONNECTION_BANDWIDTH_RECEIVED_LAST_MINUTE_TOTAL,     ///< UInt64. Bytes per second received, averaged over the last minute.
    CONNECTION_DUMMY_0,
    CONNECTION_DUMMY_1,
    CONNECTION_DUMMY_2,
    CONNECTION_DUMMY_3,
    CONNECTION_DUMMY_4,
    CONNECTION_DUMMY_5,
    CONNECTION_DUMMY_6,
    CONNECTION_DUMMY_7,
    CONNECTION_DUMMY_8,
    CONNECTION_DUMMY_9,
    CONNECTION_FILETRANSFER_BANDWIDTH_SENT,       ///< UInt64. Current file transfer upstream activity in bytes per second.
                                                  ///< Only available on request (\ref ts3client_requestServerConnectionInfo).
    CONNECTION_FILETRANSFER_BANDWIDTH_RECEIVED,   ///< UInt64. Current file transfer downstream activity in bytes per
                                                  ///< second. Only available on request (\ref
                                                  ///< ts3client_requestServerConnectionInfo).
    CONNECTION_FILETRANSFER_BYTES_RECEIVED_TOTAL, ///< UInt64. Total downstream traffic, in bytes, used for file
                                                  ///< transfer since the server was started. Only available on request
                                                  ///< (\ref ts3client_requestServerConnectionInfo).
    CONNECTION_FILETRANSFER_BYTES_SENT_TOTAL,     ///< UInt64. Total upstream traffic, in bytes, used for file transfer
                                                  ///< since the server was started. Only available on request (\ref
                                                  ///< ts3client_requestServerConnectionInfo).
    CONNECTION_ENDMARKER
};

/**
 * Describes a client position in 3 dimensional space, used for 3D Sound.
 */
typedef struct {
    float x; ///< X co-ordinate in 3D space.
    float y; ///< Y co-ordinate in 3D space.
    float z; ///< Z co-ordinate in 3D space.
} TS3_VECTOR;

enum GroupWhisperType {
    GROUPWHISPERTYPE_SERVERGROUP      = 0, ///< Whisper list consists of server groups
    GROUPWHISPERTYPE_CHANNELGROUP     = 1, ///< Whisper list consists of channel groups
    GROUPWHISPERTYPE_CHANNELCOMMANDER = 2, ///< whisper to channel commanders
    GROUPWHISPERTYPE_ALLCLIENTS       = 3, ///< whisper to all clients
    GROUPWHISPERTYPE_ENDMARKER,
};

enum GroupWhisperTargetMode {
    GROUPWHISPERTARGETMODE_ALL                   = 0,
    GROUPWHISPERTARGETMODE_CURRENTCHANNEL        = 1, ///< Whisper the current channel of the client
    GROUPWHISPERTARGETMODE_PARENTCHANNEL         = 2, ///< Whisper the parent channel of whatever channel the client is currently in
    GROUPWHISPERTARGETMODE_ALLPARENTCHANNELS     = 3, ///< Whipser to the parent channel and all their parent channels as well
    GROUPWHISPERTARGETMODE_CHANNELFAMILY         = 4, ///< Whisper to the current channel and all its sub channels
    GROUPWHISPERTARGETMODE_ANCESTORCHANNELFAMILY = 5, ///< Whisper to the current channel, all its parent and sub channels.
    GROUPWHISPERTARGETMODE_SUBCHANNELS           = 6, ///< Whisper to all sub channels of the current channel of the client
    GROUPWHISPERTARGETMODE_ENDMARKER,
};

enum MonoSoundDestination {
    MONO_SOUND_DESTINATION_ALL                  = 0, ///< Send mono sound to all available speakers
    MONO_SOUND_DESTINATION_FRONT_CENTER         = 1, ///< Send mono sound to front center speaker if available
    MONO_SOUND_DESTINATION_FRONT_LEFT_AND_RIGHT = 2  ///< Send mono sound to front left/right speakers if available
};

enum SecuritySaltOptions {
    SECURITY_SALT_CHECK_NICKNAME  = 1, ///< put nickname into security hash
    SECURITY_SALT_CHECK_META_DATA = 2  ///< put meta data into security hash
};

/*this enum is used to disable client commands on the server*/
enum ClientCommand {
    CLIENT_COMMAND_requestConnectionInfo = 0,        ///< disable client connection info request (client bandwidth usage, ip,
                                                     ///< port, ping)
    CLIENT_COMMAND_requestClientMove            = 1, ///< disable moving clients
    CLIENT_COMMAND_requestXXMuteClients         = 2, ///< disable muting other clients
    CLIENT_COMMAND_requestClientKickFromXXX     = 3, ///< disable kicking clients
    CLIENT_COMMAND_flushChannelCreation         = 4, ///< disable creating channels
    CLIENT_COMMAND_flushChannelUpdates          = 5, ///< disable editing channels
    CLIENT_COMMAND_requestChannelMove           = 6, ///< disable moving channels
    CLIENT_COMMAND_requestChannelDelete         = 7, ///< disable deleting channels
    CLIENT_COMMAND_requestChannelDescription    = 8, ///< disable channel descriptions
    CLIENT_COMMAND_requestChannelXXSubscribeXXX = 9, ///< disable being able to see clients in channels other than the
                                                     ///< current channel the client is in
    CLIENT_COMMAND_requestServerConnectionInfo = 10, ///< disable server connection info request (server bandwidth
                                                     ///< usage, ip, port, ping)
    CLIENT_COMMAND_requestSendXXXTextMsg = 11,       ///< disable text messaging
    CLIENT_COMMAND_filetransfers         = 12,       ///< disable file transfer
    CLIENT_COMMAND_ENDMARKER
};

/* Access Control List*/
enum ACLType { ACL_NONE = 0, ACL_WHITE_LIST = 1, ACL_BLACK_LIST = 2 };

/* file transfer actions*/
enum FTAction {
    FT_INIT_SERVER = 0,  ///< The virtual server is created. result->channelPath can be changed to create a different
                         ///< directory than the default 'virtualserver_x' where x is the virtual server.
    FT_INIT_CHANNEL = 1, ///< A channel is created. result->channelPath can be changed to create a different directory
                         ///< then the default 'channel_x' where x is the channel id.
    FT_UPLOAD    = 2,    ///< A file is being uploaded. All values in the result struct can be modified.
    FT_DOWNLOAD  = 3,    ///< A file is being downloaded. All values in the result struct can be modified.
    FT_DELETE    = 4,    ///< A file is being deleted. All values in the result struct can be modified.
    FT_CREATEDIR = 5,    ///< A directory is being created in a channel. All values in the result struct can be modified.
    FT_RENAME    = 6,    ///< A file or folder is being renamed. The callback will be called twice! Once for the old and then
                         ///< for the new name. All values in the result struct can be modified.
    FT_FILELIST = 7,     ///< A directory listing is requested. All values in the result struct can be modified.
    FT_FILEINFO = 8      ///< Information of a file is requested. All values in the result struct can be modified.
};

/* file transfer status */
enum FileTransferState {
    FILETRANSFER_INITIALISING = 0, ///< File transfer is establishing connection.
    FILETRANSFER_ACTIVE,           ///< File transfer is in progress
    FILETRANSFER_FINISHED,         ///< File transfer has finished
};

/* file transfer types */
enum FileTransferType {
    FileListType_Directory = 0, ///< The file entry is a directory
    FileListType_File,          ///< The file entry is a regular file
};

/* some structs to handle variables in callbacks */
#define MAX_VARIABLES_EXPORT_COUNT 64
struct VariablesExportItem {
    unsigned char itemIsValid;   ///< Whether or not there is any data in this item. Ignore this item if this is 0.
    unsigned char proposedIsSet; ///< The value in proposed is set. If 0 ignore proposed
    const char*   current;       ///< current value (stored in memory)
    const char*   proposed;      ///< New value to change to (const, so no updates please)
};

struct VariablesExport {
    struct VariablesExportItem items[MAX_VARIABLES_EXPORT_COUNT];
};

struct ClientMiniExport {
    anyID       ID;       ///< id of the client
    uint64      channel;  ///< the channel the client is in
    const char* ident;    ///< client public identity
    const char* nickname; ///< client display name
};

/**
 * Structure used to describe a file transfer in the \ref ServerLibFunctions.onTransformFilePath callback.
 * This describes the original values, and also contains hints for length limitations of the result parameter
 * of the callback.
 * \verbatim embed:rst
   .. important::
      Which values of the struct can be modified is defined by the action value of the original parameter.
   \endverbatim
 */
struct TransformFilePathExport {
    uint64      channel;            ///< The channel id of the file. 0 if action is \ref FT_INIT_SERVER
    const char* filename;           ///< utf8 encoded c string containing the original file name as intended by the client.
    int         action;             ///< The action to be performed. One of the values from the \ref FTAction enum. Defines which values of
                                    ///< the result struct can be modified.
    int transformedFileNameMaxSize; ///< The maximum length the file name can be rewritten to.
    int channelPathMaxSize;         ///< The maximum length the path can be rewritten to.
};

/**
 * Structure to rewrite the file transfer file name and path in the \ref ServerLibFunctions.onTransformFilePath callback.
 * The lengths are limited as described in the original parameter.
 * \verbatim embed:rst
   .. important::
      Which values of the struct can be modified is defined by the action value of the original parameter.
   \endverbatim
 */
struct TransformFilePathExportReturns {
    char* transformedFileName; ///< pointer to target file name. Fill the memory pointed to with an utf8 encoded c string
                               ///< containing the new file name. Limited to original->transformedFileNameMaxSize bytes.
    char* channelPath;         ///< pointer to memory for new path. Fill the memory pointed to with an utf8 encoded c string
                               ///< containing the new path. Limited to original->channelPathMaxSize bytes.
    int logFileAction;         ///< boolean (1/0). Whether to log this file transfer to the log. Action is not logged regardless
                               ///< of this value if the servers \ref VIRTUALSERVER_LOG_FILETRANSFER property is 0.
};

struct FileTransferCallbackExport {
    anyID        clientID;         ///< the client who started the file transfer
    anyID        transferID;       ///< local identifier of the transfer that has completed
    anyID        remoteTransferID; ///< remote identifier of the transfer that has completed
    unsigned int status;           ///< status of the transfer. One of the values from the \ref FileTransferState enum
    const char*  statusMessage;    ///< utf8 encoded c string containing a human readable description of the status
    uint64       remotefileSize;   ///< size in bytes of the complete file to be transferred
    uint64       bytes;            ///< number of bytes transferred. Same as remotefileSize when the transfer completed entirely.
    int          isSender;         ///< boolean. 1 if the server is sending the file. 0 if the server is receiving the file.
};

/*define for file transfer bandwith limits*/
#define BANDWIDTH_LIMIT_UNLIMITED 0xFFFFFFFFFFFFFFFFll

/*defines for speaker locations used by some sound callbacks*/
#ifndef SPEAKER_FRONT_LEFT
#define SPEAKER_FRONT_LEFT 0x1
#define SPEAKER_FRONT_RIGHT 0x2
#define SPEAKER_FRONT_CENTER 0x4
#define SPEAKER_LOW_FREQUENCY 0x8
#define SPEAKER_BACK_LEFT 0x10
#define SPEAKER_BACK_RIGHT 0x20
#define SPEAKER_FRONT_LEFT_OF_CENTER 0x40
#define SPEAKER_FRONT_RIGHT_OF_CENTER 0x80
#define SPEAKER_BACK_CENTER 0x100
#define SPEAKER_SIDE_LEFT 0x200
#define SPEAKER_SIDE_RIGHT 0x400
#define SPEAKER_TOP_CENTER 0x800
#define SPEAKER_TOP_FRONT_LEFT 0x1000
#define SPEAKER_TOP_FRONT_CENTER 0x2000
#define SPEAKER_TOP_FRONT_RIGHT 0x4000
#define SPEAKER_TOP_BACK_LEFT 0x8000
#define SPEAKER_TOP_BACK_CENTER 0x10000
#define SPEAKER_TOP_BACK_RIGHT 0x20000
#endif
#define SPEAKER_HEADPHONES_LEFT 0x10000000
#define SPEAKER_HEADPHONES_RIGHT 0x20000000
#define SPEAKER_MONO 0x40000000

#endif /*PUBLIC_DEFINITIONS_H*/
