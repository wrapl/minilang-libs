.. include:: <isonum.txt>

.. include:: <isoamsa.txt>

.. include:: <isotech.txt>

net/curl
========

.. rst-class:: mini-api

:mini:`fun curl(): curl`
   Returns a new Curl easy instance.


:mini:`type curl::info < enum`
   * :mini:`::EffectiveUrl`
   * :mini:`::ContentType`
   * :mini:`::Private`
   * :mini:`::FtpEntryPath`
   * :mini:`::RedirectUrl`
   * :mini:`::PrimaryIp`
   * :mini:`::RtspSessionId`
   * :mini:`::LocalIp`
   * :mini:`::Scheme`
   * :mini:`::EffectiveMethod`
   * :mini:`::Referer`
   * :mini:`::Cainfo`
   * :mini:`::Capath`
   * :mini:`::ResponseCode`
   * :mini:`::HeaderSize`
   * :mini:`::RequestSize`
   * :mini:`::SslVerifyresult`
   * :mini:`::Filetime`
   * :mini:`::RedirectCount`
   * :mini:`::HttpConnectcode`
   * :mini:`::HttpauthAvail`
   * :mini:`::ProxyauthAvail`
   * :mini:`::OsErrno`
   * :mini:`::NumConnects`
   * :mini:`::ConditionUnmet`
   * :mini:`::RtspClientCseq`
   * :mini:`::RtspServerCseq`
   * :mini:`::RtspCseqRecv`
   * :mini:`::PrimaryPort`
   * :mini:`::LocalPort`
   * :mini:`::HttpVersion`
   * :mini:`::ProxySslVerifyresult`
   * :mini:`::ProxyError`
   * :mini:`::UsedProxy`
   * :mini:`::HttpauthUsed`
   * :mini:`::ProxyauthUsed`
   * :mini:`::TotalTime`
   * :mini:`::NamelookupTime`
   * :mini:`::ConnectTime`
   * :mini:`::PretransferTime`
   * :mini:`::StarttransferTime`
   * :mini:`::RedirectTime`
   * :mini:`::AppconnectTime`
   * :mini:`::SizeUploadT`
   * :mini:`::SizeDownloadT`
   * :mini:`::SpeedDownloadT`
   * :mini:`::SpeedUploadT`
   * :mini:`::FiletimeT`
   * :mini:`::ContentLengthDownloadT`
   * :mini:`::ContentLengthUploadT`
   * :mini:`::TotalTimeT`
   * :mini:`::NamelookupTimeT`
   * :mini:`::ConnectTimeT`
   * :mini:`::PretransferTimeT`
   * :mini:`::StarttransferTimeT`
   * :mini:`::RedirectTimeT`
   * :mini:`::AppconnectTimeT`
   * :mini:`::RetryAfter`
   * :mini:`::XferId`
   * :mini:`::ConnId`
   * :mini:`::QueueTimeT`
   * :mini:`::PosttransferTimeT`
   * :mini:`::EarlydataSentT`
   * :mini:`::SizeDelivered`
   * :mini:`::SslEngines`
   * :mini:`::Cookielist`
   * :mini:`::Certinfo`
   * :mini:`::TlsSslPtr`
   * :mini:`::Activesocket`


:mini:`type curl::option < enum`
   * :mini:`::Writedata` - This is the FILE * or void * the regular output should be written to.
   * :mini:`::Readdata` - Specified file stream to upload from (use as input):
   * :mini:`::Headerdata` - send FILE * or void * to store headers to, if you use a callback it
   * :mini:`::Xferinfodata` - Data passed to the CURLOPT_PROGRESSFUNCTION and CURLOPT_XFERINFOFUNCTION
   * :mini:`::Debugdata` - set the data for the debug function
   * :mini:`::SslCtxData` - Set the userdata for the ssl context callback function's third
   * :mini:`::Sockoptdata` - 
   * :mini:`::Opensocketdata` - 
   * :mini:`::Seekdata` - 
   * :mini:`::SshKeydata` - set the SSH host key callback custom pointer
   * :mini:`::Interleavedata` - The stream to pass to INTERLEAVEFUNCTION.
   * :mini:`::ChunkData` - Let the application define custom chunk data pointer
   * :mini:`::FnmatchData` - FNMATCH_FUNCTION user pointer
   * :mini:`::Closesocketdata` - 
   * :mini:`::ResolverStartData` - User data to pass to the resolver start callback.
   * :mini:`::Trailerdata` - pointer to be passed to HTTP_TRAILER_FUNCTION
   * :mini:`::Hstsreaddata` - 
   * :mini:`::Hstswritedata` - 
   * :mini:`::Prereqdata` - Data passed to the CURLOPT_PREREQFUNCTION callback
   * :mini:`::SshHostkeydata` - set the SSH host key callback custom pointer
   * :mini:`::Url` - The full URL to get/put
   * :mini:`::Proxy` - Name of proxy to use.
   * :mini:`::Userpwd` - "user:password;options" to use when fetching.
   * :mini:`::Proxyuserpwd` - "user:password" to use with proxy.
   * :mini:`::Range` - Range to get, specified as an ASCII string.
   * :mini:`::Referer` - 
   * :mini:`::Ftpport` - Set the FTP PORT string (interface name, named or numerical IP address)
   * :mini:`::Useragent` - Set the User-Agent string (examined by some CGIs)
   * :mini:`::Cookie` - Set cookie in request:
   * :mini:`::Sslcert` - name of the file keeping your private SSL-certificate
   * :mini:`::Keypasswd` - password for the SSL or SSH private key
   * :mini:`::Cookiefile` - point to a file to read the initial cookies from, also enables
   * :mini:`::Customrequest` - Custom request, for customizing the get command like
   * :mini:`::Interface` - Set the interface string to use as outgoing network interface
   * :mini:`::Cainfo` - 
   * :mini:`::Cookiejar` - Specify which filename to write all known cookies in after completed
   * :mini:`::SslCipherList` - Specify which TLS 1.2 (1.1, 1.0) ciphers to use
   * :mini:`::Sslcerttype` - type of the file keeping your SSL-certificate ("DER", "PEM", "ENG")
   * :mini:`::Sslkey` - name of the file keeping your private SSL-key
   * :mini:`::Sslkeytype` - type of the file keeping your private SSL-key ("DER", "PEM", "ENG")
   * :mini:`::Sslengine` - crypto engine for the SSL-sub system
   * :mini:`::Capath` - 
   * :mini:`::AcceptEncoding` - Set the Accept-Encoding string. Use this to tell a server you would like
   * :mini:`::NetrcFile` - Set this option to the filename of your .netrc file you want libcurl
   * :mini:`::FtpAccount` - null-terminated string for pass on to the FTP server when asked for
   * :mini:`::Cookielist` - 
   * :mini:`::FtpAlternativeToUser` - Pointer to command string to send if USER/PASS fails.
   * :mini:`::SshPublicKeyfile` - Used by scp/sftp to do public/private key authentication
   * :mini:`::SshPrivateKeyfile` - 
   * :mini:`::Crlfile` - CRL file
   * :mini:`::Issuercert` - Issuer certificate
   * :mini:`::Username` - "name" and "pwd" to use when fetching.
   * :mini:`::Password` - 
   * :mini:`::Proxyusername` - "name" and "pwd" to use with Proxy when fetching.
   * :mini:`::Proxypassword` - 
   * :mini:`::Noproxy` - Comma separated list of hostnames defining no-proxy zones. These should
   * :mini:`::SshKnownhosts` - set the SSH knownhost filename to use
   * :mini:`::MailFrom` - set the SMTP mail originator
   * :mini:`::RtspSessionId` - 
   * :mini:`::RtspStreamUri` - The RTSP stream URI
   * :mini:`::RtspTransport` - The Transport: header to use in RTSP requests
   * :mini:`::TlsauthUsername` - Set a username for authenticated TLS
   * :mini:`::TlsauthPassword` - Set a password for authenticated TLS
   * :mini:`::TlsauthType` - Set authentication type for authenticated TLS
   * :mini:`::DnsServers` - Set the name servers to use for DNS resolution.
   * :mini:`::MailAuth` - Set the SMTP auth originator
   * :mini:`::DnsInterface` - Set the interface string to use as outgoing network
   * :mini:`::LoginOptions` - Set authentication options directly
   * :mini:`::Pinnedpublickey` - The public key used to validate the peer public key
   * :mini:`::UnixSocketPath` - Path to Unix domain socket
   * :mini:`::ProxyServiceName` - Proxy Service Name
   * :mini:`::ServiceName` - Service Name
   * :mini:`::DefaultProtocol` - Set the protocol used when curl is given a URL without a protocol
   * :mini:`::ProxyCainfo` - The CApath or CAfile used to validate the proxy certificate
   * :mini:`::ProxyCapath` - The CApath directory used to validate the proxy certificate
   * :mini:`::ProxyTlsauthUsername` - Set a username for authenticated TLS for proxy
   * :mini:`::ProxyTlsauthPassword` - Set a password for authenticated TLS for proxy
   * :mini:`::ProxyTlsauthType` - Set authentication type for authenticated TLS for proxy
   * :mini:`::ProxySslcert` - name of the file keeping your private SSL-certificate for proxy
   * :mini:`::ProxySslcerttype` - type of the file keeping your SSL-certificate ("DER", "PEM", "ENG") for
   * :mini:`::ProxySslkey` - name of the file keeping your private SSL-key for proxy
   * :mini:`::ProxySslkeytype` - type of the file keeping your private SSL-key ("DER", "PEM", "ENG") for
   * :mini:`::ProxyKeypasswd` - password for the SSL private key for proxy
   * :mini:`::ProxySslCipherList` - Specify which TLS 1.2 (1.1, 1.0) ciphers to use for proxy
   * :mini:`::ProxyCrlfile` - CRL file for proxy
   * :mini:`::PreProxy` - Name of pre proxy to use.
   * :mini:`::ProxyPinnedpublickey` - The public key in DER form used to validate the proxy public key
   * :mini:`::AbstractUnixSocket` - Path to an abstract Unix domain socket
   * :mini:`::RequestTarget` - The request target, instead of extracted from the URL
   * :mini:`::DohUrl` - DNS-over-HTTPS URL
   * :mini:`::Altsvc` - alt-svc cache filename to possibly read from/write to
   * :mini:`::SaslAuthzid` - SASL authorization identity
   * :mini:`::ProxyIssuercert` - Issuer certificate for proxy
   * :mini:`::SslEcCurves` - the EC curves requested by the TLS client (RFC 8422, 5.1);
   * :mini:`::Hsts` - HSTS filename
   * :mini:`::ProtocolsStr` - specify which protocols that are allowed to be used for the transfer,
   * :mini:`::RedirProtocolsStr` - specify which protocols that libcurl is allowed to follow directs to
   * :mini:`::HaproxyClientIp` - set a specific client IP for HAProxy PROXY protocol header?
   * :mini:`::Ech` - set ECH configuration
   * :mini:`::SslSignatureAlgorithms` - set TLS supported signature algorithms
   * :mini:`::Port` - Port number to connect to, if other than default.
   * :mini:`::Timeout` - Time-out the read operation after this amount of seconds
   * :mini:`::Infilesize` - If CURLOPT_READDATA is used, this can be used to inform libcurl about
   * :mini:`::LowSpeedLimit` - Set the "low speed limit"
   * :mini:`::LowSpeedTime` - Set the "low speed time"
   * :mini:`::ResumeFrom` - Set the continuation offset.
   * :mini:`::Crlf` - send TYPE parameter?
   * :mini:`::Timevalue` - Time to use with the above condition. Specified in number of seconds
   * :mini:`::Verbose` - talk a lot
   * :mini:`::Header` - throw the header out too
   * :mini:`::Noprogress` - shut off the progress meter
   * :mini:`::Nobody` - use HEAD to get http document
   * :mini:`::Failonerror` - no output on http error codes >= 400
   * :mini:`::Upload` - this is an upload
   * :mini:`::Post` - HTTP POST method
   * :mini:`::Dirlistonly` - bare names when listing directories
   * :mini:`::Append` - Append instead of overwrite on upload!
   * :mini:`::Followlocation` - use Location: Luke!
   * :mini:`::Transfertext` - transfer data in text/ASCII format
   * :mini:`::Autoreferer` - We want the referrer field set automatically when following locations
   * :mini:`::Proxyport` - Port of the proxy, can be set in the proxy string as well with:
   * :mini:`::Postfieldsize` - size of the POST input data, if strlen() is not good to use
   * :mini:`::Httpproxytunnel` - tunnel non-http operations through an HTTP proxy
   * :mini:`::SslVerifypeer` - Set if we should verify the peer in ssl handshake, set 1 to verify.
   * :mini:`::Maxredirs` - Maximum number of http redirects to follow
   * :mini:`::Filetime` - 
   * :mini:`::Maxconnects` - Max amount of cached alive connections
   * :mini:`::FreshConnect` - Set to explicitly use a new connection for the upcoming transfer.
   * :mini:`::ForbidReuse` - Set to explicitly forbid the upcoming transfer's connection to be reused
   * :mini:`::Connecttimeout` - Time-out connect operations after this amount of seconds, if connects are
   * :mini:`::Httpget` - Set this to force the HTTP request to get back to GET. Only really usable
   * :mini:`::SslVerifyhost` - Set if we should verify the Common name from the peer certificate in ssl
   * :mini:`::FtpUseEpsv` - Specifically switch on or off the FTP engine's use of the EPSV command. By
   * :mini:`::SslengineDefault` - set the crypto engine for the SSL-sub system as default
   * :mini:`::DnsCacheTimeout` - DNS cache timeout
   * :mini:`::Cookiesession` - mark this as start of a cookie session
   * :mini:`::Buffersize` - Instruct libcurl to use a smaller receive buffer
   * :mini:`::Nosignal` - Instruct libcurl to not use any signal/alarm handlers, even when using
   * :mini:`::UnrestrictedAuth` - Continue to send authentication (user+password) when following locations,
   * :mini:`::FtpUseEprt` - Specifically switch on or off the FTP engine's use of the EPRT command (
   * :mini:`::FtpCreateMissingDirs` - FTP Option that causes missing dirs to be created on the remote server.
   * :mini:`::ServerResponseTimeout` - Option that changes the timeout, in seconds, associated with getting a
   * :mini:`::Maxfilesize` - 
   * :mini:`::TcpNodelay` - Enable/disable the TCP Nagle algorithm
   * :mini:`::IgnoreContentLength` - ignore Content-Length
   * :mini:`::FtpSkipPasvIp` - Set to non-zero to skip the IP address received in a 227 PASV FTP server
   * :mini:`::Localport` - Local port number to bind the socket to
   * :mini:`::Localportrange` - Number of ports to try, including the first one set with LOCALPORT.
   * :mini:`::ConnectOnly` - no transfer, set up connection and let application use the socket by
   * :mini:`::SslSessionidCache` - set to 0 to disable session ID reuse for this transfer, default is
   * :mini:`::FtpSslCcc` - Send CCC (Clear Command Channel) after authentication
   * :mini:`::TimeoutMs` - Same as TIMEOUT and CONNECTTIMEOUT, but with ms resolution
   * :mini:`::ConnecttimeoutMs` - 
   * :mini:`::HttpTransferDecoding` - set to zero to disable the libcurl's decoding and thus pass the raw body
   * :mini:`::HttpContentDecoding` - 
   * :mini:`::NewFilePerms` - Permission used when creating new files and directories on the remote
   * :mini:`::NewDirectoryPerms` - 
   * :mini:`::ProxyTransferMode` - set transfer mode (;type=<a|i>) when doing FTP via an HTTP proxy
   * :mini:`::AddressScope` - (IPv6) Address scope
   * :mini:`::Certinfo` - 
   * :mini:`::TftpBlksize` - block size for TFTP transfers
   * :mini:`::FtpUsePret` - FTP: send PRET before PASV
   * :mini:`::RtspClientCseq` - 
   * :mini:`::RtspServerCseq` - 
   * :mini:`::Wildcardmatch` - Turn on wildcard matching
   * :mini:`::TransferEncoding` - 
   * :mini:`::AccepttimeoutMs` - Time-out accept operations (currently for FTP only) after this amount
   * :mini:`::TcpKeepalive` - Set TCP keepalive
   * :mini:`::TcpKeepidle` - non-universal keepalive knobs (Linux, AIX, HP-UX, more)
   * :mini:`::TcpKeepintvl` - 
   * :mini:`::SaslIr` - Enable/disable SASL initial response
   * :mini:`::SslEnableAlpn` - Enable/disable TLS ALPN extension (http2 over ssl might fail without)
   * :mini:`::SslVerifystatus` - Set if we should verify the certificate status.
   * :mini:`::PathAsIs` - Do not squash dot-dot sequences
   * :mini:`::Pipewait` - Wait/do not wait for pipe/mutex to clarify
   * :mini:`::StreamWeight` - Set stream weight, 1 - 256 (default is 16)
   * :mini:`::TftpNoOptions` - Do not send any tftp option requests to the server
   * :mini:`::TcpFastopen` - Set TCP Fast Open
   * :mini:`::KeepSendingOnError` - Continue to send data if the server responds early with an
   * :mini:`::ProxySslVerifypeer` - Set if we should verify the proxy in ssl handshake,
   * :mini:`::ProxySslVerifyhost` - Set if we should verify the Common name from the proxy certificate in ssl
   * :mini:`::ProxySslOptions` - Enable/disable specific SSL features with a bitmask for proxy, see
   * :mini:`::SuppressConnectHeaders` - Suppress proxy CONNECT response headers from user callbacks
   * :mini:`::SshCompression` - Enable/disable SSH compression
   * :mini:`::HappyEyeballsTimeoutMs` - Head start in milliseconds to give happy eyeballs.
   * :mini:`::Haproxyprotocol` - send HAProxy PROXY protocol header?
   * :mini:`::DnsShuffleAddresses` - shuffle addresses before use when DNS returns multiple
   * :mini:`::DisallowUsernameInUrl` - Disallow specifying username/login in URL.
   * :mini:`::UploadBuffersize` - Preferred buffer size to use for uploads
   * :mini:`::UpkeepIntervalMs` - Time in ms between connection upkeep calls for long-lived connections.
   * :mini:`::AltsvcCtrl` - alt-svc control bitmask
   * :mini:`::MaxageConn` - maximum age (idle time) of a connection to consider it for reuse
   * :mini:`::MailRcptAllowfails` - allow RCPT TO command to fail for some recipients
   * :mini:`::HstsCtrl` - HSTS bitmask
   * :mini:`::DohSslVerifypeer` - Same as CURLOPT_SSL_VERIFYPEER but for DoH (DNS-over-HTTPS) servers.
   * :mini:`::DohSslVerifyhost` - Same as CURLOPT_SSL_VERIFYHOST but for DoH (DNS-over-HTTPS) servers.
   * :mini:`::DohSslVerifystatus` - Same as CURLOPT_SSL_VERIFYSTATUS but for DoH (DNS-over-HTTPS) servers.
   * :mini:`::MaxlifetimeConn` - maximum age (since creation) of a connection to consider it for reuse
   * :mini:`::MimeOptions` - Set MIME option flags.
   * :mini:`::WsOptions` - WebSockets options
   * :mini:`::CaCacheTimeout` - CA cache timeout
   * :mini:`::QuickExit` - Can leak things, gonna exit() soon
   * :mini:`::ServerResponseTimeoutMs` - millisecond version
   * :mini:`::TcpKeepcnt` - maximum number of keepalive probes (Linux, *BSD, macOS, etc.)
   * :mini:`::UploadFlags` - 
   * :mini:`::Errorbuffer` - Buffer to receive error messages in, must be at least CURL_ERROR_SIZE
   * :mini:`::Postfields` - POST static input fields.
   * :mini:`::Stderr` - FILE handle to use instead of stderr
   * :mini:`::Share` - Provide a CURLShare for mutexing non-ts data
   * :mini:`::Private` - 
   * :mini:`::Copypostfields` - POST volatile input fields.
   * :mini:`::StreamDepends` - Set stream dependency on another curl handle
   * :mini:`::StreamDependsE` - Set E-xclusive stream dependency on another curl handle
   * :mini:`::Mimepost` - Post MIME data.
   * :mini:`::Curlu` - Specify URL using CURL URL API.
   * :mini:`::Writefunction` - Function that is called to store the output (instead of fwrite). The
   * :mini:`::Readfunction` - Function that is called to read the input (instead of fread). The
   * :mini:`::Headerfunction` - Function that is called to store headers (instead of fwrite). The
   * :mini:`::Debugfunction` - set the debug function
   * :mini:`::SslCtxFunction` - Set the ssl context callback function, currently only for OpenSSL or
   * :mini:`::Sockoptfunction` - callback function for setting socket options
   * :mini:`::Opensocketfunction` - Callback function for opening socket (instead of socket(2)). Optionally,
   * :mini:`::Seekfunction` - Callback function for seeking in the input stream
   * :mini:`::SshKeyfunction` - set the SSH host key callback, must point to a curl_sshkeycallback
   * :mini:`::Interleavefunction` - Let the application define a custom write method for RTP data
   * :mini:`::ChunkBgnFunction` - Directory matching callback called before downloading of an
   * :mini:`::ChunkEndFunction` - Directory matching callback called after the file (chunk)
   * :mini:`::FnmatchFunction` - Change match (fnmatch-like) callback for wildcard matching
   * :mini:`::Closesocketfunction` - Callback function for closing socket (instead of close(2)). The callback
   * :mini:`::Xferinfofunction` - Function that is called instead of the internal progress display
   * :mini:`::ResolverStartFunction` - Function that is called before a resolver request is made
   * :mini:`::Trailerfunction` - add trailing data after no more data is available
   * :mini:`::Hstsreadfunction` - HSTS read callback
   * :mini:`::Hstswritefunction` - HSTS write callback
   * :mini:`::Prereqfunction` - Function that is called immediately before the initial request
   * :mini:`::SshHostkeyfunction` - set the SSH host key callback, must point to a curl_sshkeycallback
   * :mini:`::Httpheader` - This points to a linked list of headers, struct curl_slist kind. This
   * :mini:`::Quote` - send linked-list of QUOTE commands
   * :mini:`::Postquote` - send linked-list of post-transfer QUOTE commands
   * :mini:`::Telnetoptions` - This points to a linked list of telnet options
   * :mini:`::Prequote` - send linked-list of pre-transfer QUOTE commands
   * :mini:`::MailRcpt` - set the list of SMTP mail receiver(s)
   * :mini:`::Resolve` - send linked-list of name:port:address sets
   * :mini:`::Proxyheader` - This points to a linked list of headers used for proxy requests only,
   * :mini:`::ConnectTo` - Linked-list of host:port:connect-to-host:connect-to-port,
   * :mini:`::Sslversion` - What version to specifically try to use.
   * :mini:`::Timecondition` - What kind of HTTP time condition to use, see defines
   * :mini:`::Netrc` - Specify whether to read the user+password from the .netrc or the URL.
   * :mini:`::HttpVersion` - 
   * :mini:`::Proxytype` - indicates type of proxy. accepted values are CURLPROXY_HTTP (default),
   * :mini:`::Httpauth` - Set this to a bitmask value to enable the particular authentications
   * :mini:`::Proxyauth` - Set this to a bitmask value to enable the particular authentications
   * :mini:`::Ipresolve` - Set this option to one of the CURL_IPRESOLVE_* defines (see below) to
   * :mini:`::UseSsl` - Enable SSL/TLS for FTP, pick one of:
   * :mini:`::Ftpsslauth` - 
   * :mini:`::FtpFilemethod` - Select "file method" to use when doing FTP, see the curl_ftpmethod
   * :mini:`::SshAuthTypes` - allowed SSH authentication methods
   * :mini:`::Postredir` - Set the behavior of POST when redirecting. Values must be set to one
   * :mini:`::RtspRequest` - RTSP request method (OPTIONS, SETUP, PLAY, etc...)
   * :mini:`::GssapiDelegation` - allow GSSAPI credential delegation
   * :mini:`::SslOptions` - Enable/disable specific SSL features with a bitmask, see CURLSSLOPT_*
   * :mini:`::Headeropt` - Pass in a bitmask of "header options"
   * :mini:`::ProxySslversion` - What version to specifically try to use for proxy.
   * :mini:`::InfilesizeLarge` - See the comment for INFILESIZE above, but in short, specifies
   * :mini:`::ResumeFromLarge` - Sets the continuation offset. There is also a CURLOPTTYPE_LONG version
   * :mini:`::MaxfilesizeLarge` - Sets the maximum size of data that is to be downloaded from
   * :mini:`::PostfieldsizeLarge` - The _LARGE version of the standard POSTFIELDSIZE option
   * :mini:`::MaxSendSpeedLarge` - if the connection proceeds too quickly then need to slow it down limit-rate: maximum number of bytes per second to send or receive
   * :mini:`::MaxRecvSpeedLarge` - 
   * :mini:`::TimevalueLarge` - Time to use with the CURLOPT_TIMECONDITION. Specified in number of
   * :mini:`::SslcertBlob` - the private SSL-certificate as a "blob"
   * :mini:`::SslkeyBlob` - 
   * :mini:`::ProxySslcertBlob` - 
   * :mini:`::ProxySslkeyBlob` - 
   * :mini:`::IssuercertBlob` - 
   * :mini:`::ProxyIssuercertBlob` - 
   * :mini:`::CainfoBlob` - The CA certificates as "blob" used to validate the peer certificate
   * :mini:`::ProxyCainfoBlob` - The CA certificates as "blob" used to validate the proxy certificate


:mini:`type curlusessl < enum`
   * :mini:`::None`
   * :mini:`::Try`
   * :mini:`::Control`
   * :mini:`::All`


:mini:`meth (Arg₁: curl):get(Arg₂: curlinfoset)`
   *TBD*


:mini:`meth (Arg₁: curl):get(Arg₂: curlinfostring)`
   *TBD*


:mini:`type curlusessl < enum`
   * :mini:`::None`
   * :mini:`::Try`
   * :mini:`::Control`
   * :mini:`::All`


:mini:`meth (Arg₁: curl):get(Arg₂: curlinfointeger)`
   *TBD*


:mini:`meth (Arg₁: curl):cleanup`
   *TBD*


:mini:`meth (Arg₁: curl):reset`
   *TBD*


:mini:`meth (Arg₁: curl):perform`
   *TBD*


:mini:`meth (Curl: curl):set(Option: curloptionfunction, Value: function): curl`
   Sets :mini:`Option` in :mini:`Curl` to :mini:`Value`.


:mini:`meth (Curl: curl):set(Option: curloptionfunction, Value: string::buffer): curl`
   Sets :mini:`Option` in :mini:`Curl` to :mini:`Value`.


:mini:`meth (Curl: curl):set(Option: curloptionfunction, Value: stream): curl`
   Sets :mini:`Option` in :mini:`Curl` to :mini:`Value`.


:mini:`meth (Curl: curl):set(Option: curloptionset, Value: list): curl`
   Sets :mini:`Option` in :mini:`Curl` to :mini:`Value`.


:mini:`meth (Curl: curl):set(Option: curloptionstring, Value: string): curl`
   Sets :mini:`Option` in :mini:`Curl` to :mini:`Value`.


:mini:`meth (Curl: curl):set(Option: curloptioninteger, Value: boolean): curl`
   Sets :mini:`Option` in :mini:`Curl` to :mini:`Value`.


:mini:`meth (Curl: curl):set(Option: curloptionenum, Value: enum::value): curl`
   Sets :mini:`Option` in :mini:`Curl` to :mini:`Value`.


:mini:`meth (Curl: curl):set(Option: curloptioninteger, Value: integer): curl`
   Sets :mini:`Option` in :mini:`Curl` to :mini:`Value`.


:mini:`meth (Curl: curl):set(Option: curloption, nil: nil): curl`
   Sets :mini:`Option` in :mini:`Curl` to :mini:`nil`.


:mini:`type curl`
   *TBD*


:mini:`fun curl(): curl`
   Returns a new Curl easy instance.


:mini:`meth (Arg₁: curl):get(Arg₂: curlinforeal)`
   *TBD*


:mini:`meth (Arg₁: curl):get(Arg₂: curlinfoset)`
   *TBD*


:mini:`meth (Arg₁: curl):get(Arg₂: curlinfostring)`
   *TBD*


:mini:`meth (Arg₁: curl):get(Arg₂: curlinforeal)`
   *TBD*


:mini:`meth (Arg₁: curl):get(Arg₂: curlinfointeger)`
   *TBD*


:mini:`meth (Arg₁: curl):perform`
   *TBD*


:mini:`meth (Curl: curl):set(Option: curloptionfunction, Value: function): curl`
   Sets :mini:`Option` in :mini:`Curl` to :mini:`Value`.


:mini:`meth (Curl: curl):set(Option: curloptionfunction, Value: stream): curl`
   Sets :mini:`Option` in :mini:`Curl` to :mini:`Value`.


:mini:`meth (Curl: curl):set(Option: curloptionset, Value: list): curl`
   Sets :mini:`Option` in :mini:`Curl` to :mini:`Value`.


:mini:`meth (Curl: curl):set(Option: curloptionstring, Value: string): curl`
   Sets :mini:`Option` in :mini:`Curl` to :mini:`Value`.


:mini:`meth (Curl: curl):set(Option: curloptioninteger, Value: boolean): curl`
   Sets :mini:`Option` in :mini:`Curl` to :mini:`Value`.


:mini:`meth (Curl: curl):set(Option: curloptionenum, Value: enum::value): curl`
   Sets :mini:`Option` in :mini:`Curl` to :mini:`Value`.


:mini:`meth (Curl: curl):set(Option: curloptioninteger, Value: integer): curl`
   Sets :mini:`Option` in :mini:`Curl` to :mini:`Value`.


:mini:`meth (Curl: curl):set(Option: curloption, nil: nil): curl`
   Sets :mini:`Option` in :mini:`Curl` to :mini:`nil`.


:mini:`type curl`
   *TBD*


