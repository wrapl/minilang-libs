#include <minilang/ml_library.h>
#include <minilang/ml_macros.h>
#include <minilang/ml_object.h>
#include <minilang/ml_stream.h>
#include <curl/curl.h>

typedef struct {
	ml_type_t *Type;
	CURL *Handle;
} curl_t;

extern ml_type_t CurlT[];

static int progress_callback(curl_t *Curl, curl_off_t DLTotal, curl_off_t DLNow, curl_off_t ULTotal, curl_off_t ULNow) {
	for (;;) {
		ml_queued_state_t Queued = ml_scheduler_queue_next();
		if (!Queued.State) break;
		Queued.State->run(Queued.State, Queued.Value);
	}
	return CURL_PROGRESSFUNC_CONTINUE;
}

ML_FUNCTIONX(Curl) {
	curl_t *Curl = new(curl_t);
	Curl->Type = CurlT;
	Curl->Handle = curl_easy_init();
	curl_easy_setopt(Curl->Handle, CURLOPT_PRIVATE, Curl);
	curl_easy_setopt(Curl->Handle, CURLOPT_XFERINFOFUNCTION, progress_callback);
	curl_easy_setopt(Curl->Handle, CURLOPT_XFERINFODATA, Curl);
	curl_easy_setopt(Curl->Handle, CURLOPT_NOPROGRESS, 0);
	ML_RETURN(Curl);
}

ML_TYPE(CurlT, (), "curl",
	.Constructor = (ml_value_t *)Curl
);

ML_ENUM2(CurlOptionT, "curl::option",
	"Verbose", CURLOPT_VERBOSE,
	"Header", CURLOPT_HEADER,
	"NoProgress", CURLOPT_NOPROGRESS,
	"NoSignal", CURLOPT_NOSIGNAL,
	"WriteFunc", CURLOPT_WRITEFUNCTION,
	"WriteData", CURLOPT_WRITEDATA,
	"ReadFunc", CURLOPT_READFUNCTION,
	"ReadData", CURLOPT_READDATA,
	"IoctlFunc", CURLOPT_IOCTLFUNCTION,
	"IoctlData", CURLOPT_IOCTLDATA,
	"XferInfoFunc", CURLOPT_XFERINFOFUNCTION,
	"XferInfoData", CURLOPT_XFERINFODATA,
#ifdef LINUX
	"SeekFunc", CURLOPT_SEEKFUNCTION,
	"SeekData", CURLOPT_SEEKDATA,
#endif
	"SockOptFunc", CURLOPT_SOCKOPTFUNCTION,
	"SockOptData", CURLOPT_SOCKOPTDATA,
#ifdef LINUX
	"OpenSocketFunc", CURLOPT_OPENSOCKETFUNCTION,
	"OpenSocketData", CURLOPT_OPENSOCKETDATA,
#endif
	"ProgressFunc", CURLOPT_PROGRESSFUNCTION,
	"ProgressData", CURLOPT_PROGRESSDATA,
	"HeaderFunc", CURLOPT_HEADERFUNCTION,
	"WriteHeader", CURLOPT_WRITEHEADER,
	"DebugFunc", CURLOPT_DEBUGFUNCTION,
	"DebugData", CURLOPT_DEBUGDATA,
	"SslCtxFunc", CURLOPT_SSL_CTX_FUNCTION,
	"SslCtxData", CURLOPT_SSL_CTX_DATA,
	"ConvToNetworkFunc", CURLOPT_CONV_TO_NETWORK_FUNCTION,
	"ConvFromNetworkFunc", CURLOPT_CONV_FROM_NETWORK_FUNCTION,
	"ConvFromUTF8Func", CURLOPT_CONV_FROM_UTF8_FUNCTION,
	"ErrorBuffer", CURLOPT_ERRORBUFFER,
	"Stderr", CURLOPT_STDERR,
	"FailOnError", CURLOPT_FAILONERROR,
	"Url", CURLOPT_URL,
	"Proxy", CURLOPT_PROXY,
	"ProxyPort", CURLOPT_PROXYPORT,
	"ProxyType", CURLOPT_PROXYTYPE,
	"HttpProxyTunnel", CURLOPT_HTTPPROXYTUNNEL,
	"Interface", CURLOPT_INTERFACE,
	"LocalPort", CURLOPT_LOCALPORT,
	"LocalPortRange", CURLOPT_LOCALPORTRANGE,
	"DnsCacheTimeout", CURLOPT_DNS_CACHE_TIMEOUT,
	"DnsUseGlobalCache", CURLOPT_DNS_USE_GLOBAL_CACHE,
	"BufferSize", CURLOPT_BUFFERSIZE,
	"Port", CURLOPT_PORT,
	"TcpNoDelay", CURLOPT_TCP_NODELAY,
	"NetRc", CURLOPT_NETRC,
	"NetRcFile", CURLOPT_NETRC_FILE,
	"UserPwd", CURLOPT_USERPWD,
	"UserName", CURLOPT_USERNAME,
	"Password", CURLOPT_PASSWORD,
	"ProxyUserPwd", CURLOPT_PROXYUSERPWD,
	"HttpAuth", CURLOPT_HTTPAUTH,
	"ProxyAuth", CURLOPT_PROXYAUTH,
	"AutoReferer", CURLOPT_AUTOREFERER,
	"Encoding", CURLOPT_ENCODING,
	"FollowLocation", CURLOPT_FOLLOWLOCATION,
	"UnrestrictedAuth", CURLOPT_UNRESTRICTED_AUTH,
	"MaxRedirs", CURLOPT_MAXREDIRS,
	"Put", CURLOPT_PUT,
	"Post", CURLOPT_POST,
	"PostFields", CURLOPT_POSTFIELDS,
	"PostFieldSize", CURLOPT_POSTFIELDSIZE,
	"PostFieldSizeLarge", CURLOPT_POSTFIELDSIZE_LARGE,
#ifdef LINUX
	"CopyPostFields", CURLOPT_COPYPOSTFIELDS,
#endif
	"HttpPost", CURLOPT_HTTPPOST,
	"Referer", CURLOPT_REFERER,
	"UserAgent", CURLOPT_USERAGENT,
	"HttpHeader", CURLOPT_HTTPHEADER,
	"Http200Aliases", CURLOPT_HTTP200ALIASES,
	"Cookie", CURLOPT_COOKIE,
	"CookieFile", CURLOPT_COOKIEFILE,
	"CookieJar", CURLOPT_COOKIEJAR,
	"CookieSession", CURLOPT_COOKIESESSION,
	"CookieList", CURLOPT_COOKIELIST,
	"HttpGet", CURLOPT_HTTPGET,
	"HttpVersion", CURLOPT_HTTP_VERSION,
	"IgnoreContentLength", CURLOPT_IGNORE_CONTENT_LENGTH,
	"HttpContentDecoding", CURLOPT_HTTP_CONTENT_DECODING,
	"HttpTransferDecoding", CURLOPT_HTTP_TRANSFER_DECODING,
	"FtpPort", CURLOPT_FTPPORT,
	"Quote", CURLOPT_QUOTE,
	"PostQuote", CURLOPT_POSTQUOTE,
	"PreQuote", CURLOPT_PREQUOTE,
#ifdef LINUX
	"DirListOnly", CURLOPT_DIRLISTONLY,
	"Append", CURLOPT_APPEND,
#endif
	"FtpUseEprt", CURLOPT_FTP_USE_EPRT,
	"FtpUseEpsv", CURLOPT_FTP_USE_EPSV,
	"FtpCreateMissingDirs", CURLOPT_FTP_CREATE_MISSING_DIRS,
	"FtpResponseTimeout", CURLOPT_FTP_RESPONSE_TIMEOUT,
	"FtpAlternativeToUser", CURLOPT_FTP_ALTERNATIVE_TO_USER,
	"FtpSkipPasvIp", CURLOPT_FTP_SKIP_PASV_IP,
#ifdef LINUX
	"UseSsl", CURLOPT_USE_SSL,
#endif
	"FtpSslAuth", CURLOPT_FTPSSLAUTH,
	"FtpSslCcc", CURLOPT_FTP_SSL_CCC,
	"FtpAccount", CURLOPT_FTP_ACCOUNT,
	"FtpFileMethod", CURLOPT_FTP_FILEMETHOD,
	"TransferText", CURLOPT_TRANSFERTEXT,
#ifdef LINUX
	"ProxyTransferMode", CURLOPT_PROXY_TRANSFER_MODE,
#endif
	"CrLf", CURLOPT_CRLF,
	"Range", CURLOPT_RANGE,
	"ResumeFrom", CURLOPT_RESUME_FROM,
	"ResumeFromLarge", CURLOPT_RESUME_FROM_LARGE,
	"CustomRequest", CURLOPT_CUSTOMREQUEST,
	"FileTime", CURLOPT_FILETIME,
	"NoBody", CURLOPT_NOBODY,
	"InFileSize", CURLOPT_INFILESIZE,
	"InFileSizeLarge", CURLOPT_INFILESIZE_LARGE,
	"Upload", CURLOPT_UPLOAD,
	"MaxFileSize", CURLOPT_MAXFILESIZE,
	"MaxFileSizeLarge", CURLOPT_MAXFILESIZE_LARGE,
	"TimeCondition", CURLOPT_TIMECONDITION,
	"TimeValue", CURLOPT_TIMEVALUE,
	"TimeOut", CURLOPT_TIMEOUT,
	"TimeOutMs", CURLOPT_TIMEOUT_MS,
	"LowSpeedLimit", CURLOPT_LOW_SPEED_LIMIT,
	"LowSpeedTime", CURLOPT_LOW_SPEED_TIME,
	"MaxSendSpeedLarge", CURLOPT_MAX_SEND_SPEED_LARGE,
	"MaxRecvSpeedLarge", CURLOPT_MAX_RECV_SPEED_LARGE,
	"MaxConnects", CURLOPT_MAXCONNECTS,
	"ClosePolicy", CURLOPT_CLOSEPOLICY,
	"FreshConnect", CURLOPT_FRESH_CONNECT,
	"ForbidReuse", CURLOPT_FORBID_REUSE,
	"ConnectTimeout", CURLOPT_CONNECTTIMEOUT,
	"ConnectTimeoutMs", CURLOPT_CONNECTTIMEOUT_MS,
	"IpResolve", CURLOPT_IPRESOLVE,
	"ConnectOnly", CURLOPT_CONNECT_ONLY,
	"SslCert", CURLOPT_SSLCERT,
	"SslCertType", CURLOPT_SSLCERTTYPE,
	"SslKey", CURLOPT_SSLKEY,
	"SslKeyType", CURLOPT_SSLKEYTYPE,
#ifdef LINUX
	"KeyPasswd", CURLOPT_KEYPASSWD,
#endif
	"SslEngine", CURLOPT_SSLENGINE,
	"SslEngineDefault", CURLOPT_SSLENGINE_DEFAULT,
	"SslVersion", CURLOPT_SSLVERSION,
	"SslVerifyPeer", CURLOPT_SSL_VERIFYPEER,
	"CaInfo", CURLOPT_CAINFO,
	"CaPath", CURLOPT_CAPATH,
	"RandomFile", CURLOPT_RANDOM_FILE,
	"EgdSocket", CURLOPT_EGDSOCKET,
	"SslVerifyHost", CURLOPT_SSL_VERIFYHOST,
	"SslCipherList", CURLOPT_SSL_CIPHER_LIST,
	"SslSessionIdCache", CURLOPT_SSL_SESSIONID_CACHE,
#ifdef LINUX
	"KrbLevel", CURLOPT_KRBLEVEL,
#endif
	"SshAuthTypes", CURLOPT_SSH_AUTH_TYPES,
	"SshKnownHosts", CURLOPT_SSH_KNOWNHOSTS,
	"SshKeyFunc", CURLOPT_SSH_KEYFUNCTION,
#ifdef LINUX
	"SshHostPublicKeyMd5", CURLOPT_SSH_HOST_PUBLIC_KEY_MD5,
#endif
	"SshPublicKeyFile", CURLOPT_SSH_PUBLIC_KEYFILE,
	"SshPrivateKeyFile", CURLOPT_SSH_PRIVATE_KEYFILE,
	"Private", CURLOPT_PRIVATE,
	"Share", CURLOPT_SHARE,
#ifdef LINUX
	"NewFilePerms", CURLOPT_NEW_FILE_PERMS,
#endif
	"TelnetOptions", CURLOPT_TELNETOPTIONS,
	"MailFrom", CURLOPT_MAIL_FROM,
	"MailRcpt", CURLOPT_MAIL_RCPT
);

ML_METHOD("set", CurlT, CurlOptionT, MLNilT) {
	curl_t *Curl = (curl_t *)Args[0];
	CURLoption Option = ml_enum_value_value(Args[1]);
	curl_easy_setopt(Curl->Handle, Option, 0);
	return (ml_value_t *)Curl;
}

ML_METHOD("set", CurlT, CurlOptionT, MLBooleanT) {
	curl_t *Curl = (curl_t *)Args[0];
	CURLoption Option = ml_enum_value_value(Args[1]);
	curl_easy_setopt(Curl->Handle, Option, ml_boolean_value(Args[2]));
	return (ml_value_t *)Curl;
}

ML_METHOD("set", CurlT, CurlOptionT, MLIntegerT) {
	curl_t *Curl = (curl_t *)Args[0];
	CURLoption Option = ml_enum_value_value(Args[1]);
	curl_easy_setopt(Curl->Handle, Option, ml_integer_value(Args[2]));
	return (ml_value_t *)Curl;
}

ML_METHOD("set", CurlT, CurlOptionT, MLStringT) {
	curl_t *Curl = (curl_t *)Args[0];
	CURLoption Option = ml_enum_value_value(Args[1]);
	curl_easy_setopt(Curl->Handle, Option, ml_string_value(Args[2]));
	return (ml_value_t *)Curl;
}

ML_METHOD("set", CurlT, CurlOptionT, MLListT) {
	curl_t *Curl = (curl_t *)Args[0];
	CURLoption Option = ml_enum_value_value(Args[1]);
	struct curl_slist *List = NULL;
	ML_LIST_FOREACH(Args[2], Iter) List = curl_slist_append(List, ml_string_value(Iter->Value));
	curl_easy_setopt(Curl->Handle, Option, List);
	return (ml_value_t *)Curl;
}

typedef struct {
	ml_state_t Base;
	CURL *Handle;
	ml_value_t *Value, *Result;
	int Write, Paused;
} callback_state_t;

static void callback_state_run(callback_state_t *State, ml_value_t *Result) {
	State->Result = Result;
	if (State->Paused) curl_easy_pause(State->Handle, CURLPAUSE_CONT);
}

static size_t stream_read_callback(char *Buffer, size_t Size, size_t N, callback_state_t *State) {
	ml_value_t *Result = State->Result;
	if (!Result) {
		ml_stream_read((ml_state_t *)State, State->Value, Buffer, Size * N);
		if (!State->Result) {
			State->Paused = 1;
			return CURL_READFUNC_PAUSE;
		} else {
			Result = State->Result;
			State->Paused = 0;
		}
	}
	State->Result = NULL;
	if (ml_is_error(Result)) return CURL_READFUNC_ABORT;
	if (Result == MLNil) return 0;
	return ml_integer_value(Result);
}

static size_t stream_write_callback(char *Buffer, size_t Size, size_t N, callback_state_t *State) {
	ml_value_t *Result = State->Result;
	if (!Result) {
		ml_stream_write((ml_state_t *)State, State->Value, Buffer, Size * N);
		if (!State->Result) {
			State->Paused = 1;
			return CURL_WRITEFUNC_PAUSE;
		} else {
			Result = State->Result;
			State->Paused = 0;
		}
	}
	State->Result = NULL;
	if (ml_is_error(Result)) return CURL_READFUNC_ABORT;
	if (Result == MLNil) return 0;
	return ml_integer_value(Result);
}

ML_METHODX("set", CurlT, CurlOptionT, MLStreamT) {
	curl_t *Curl = (curl_t *)Args[0];
	CURLoption Option = ml_enum_value_value(Args[1]);
	callback_state_t *State = new(callback_state_t);
	State->Base.Context = Caller->Context;
	State->Base.run = (ml_state_fn)callback_state_run;
	State->Handle = Curl->Handle;
	State->Value = Args[2];
	switch (Option) {
	case CURLOPT_WRITEFUNCTION:
		curl_easy_setopt(Curl->Handle, CURLOPT_WRITEFUNCTION, stream_write_callback);
		curl_easy_setopt(Curl->Handle, CURLOPT_WRITEDATA, State);
		break;
	case CURLOPT_HEADERFUNCTION:
		curl_easy_setopt(Curl->Handle, CURLOPT_HEADERFUNCTION, stream_write_callback);
		curl_easy_setopt(Curl->Handle, CURLOPT_HEADERDATA, State);
		break;
	case CURLOPT_READFUNCTION:
		curl_easy_setopt(Curl->Handle, CURLOPT_READFUNCTION, stream_write_callback);
		curl_easy_setopt(Curl->Handle, CURLOPT_READDATA, State);
		break;
	default:
		ML_ERROR("CurlError", "Unsupported option for stream");
	}
	ML_RETURN(Curl);
}

static size_t function_callback(char *Buffer, size_t Size, size_t N, callback_state_t *State) {
	ml_value_t *Result = State->Result;
	if (!Result) {
		ml_value_t **Args = ml_alloc_args(1);
		Args[0] = State->Write ? ml_buffer(Buffer, Size * N) : ml_string(Buffer, Size * N);
		ml_call((ml_state_t *)State, State->Value, 1, Args);
		if (!State->Result) {
			State->Paused = 1;
			return CURL_READFUNC_PAUSE;
		} else {
			Result = State->Result;
			State->Paused = 0;
		}
	}
	State->Result = NULL;
	if (ml_is_error(Result)) return CURL_READFUNC_ABORT;
	if (Result == MLNil) return 0;
	return ml_integer_value(Result);
}

ML_METHODX("set", CurlT, CurlOptionT, MLFunctionT) {
	curl_t *Curl = (curl_t *)Args[0];
	CURLoption Option = ml_enum_value_value(Args[1]);
	callback_state_t *State = new(callback_state_t);
	State->Base.Context = Caller->Context;
	State->Base.run = (ml_state_fn)callback_state_run;
	State->Handle = Curl->Handle;
	State->Value = Args[2];
	switch (Option) {
	case CURLOPT_WRITEFUNCTION:
		curl_easy_setopt(Curl->Handle, CURLOPT_WRITEFUNCTION, function_callback);
		curl_easy_setopt(Curl->Handle, CURLOPT_WRITEDATA, State);
		break;
	case CURLOPT_HEADERFUNCTION:
		curl_easy_setopt(Curl->Handle, CURLOPT_HEADERFUNCTION, function_callback);
		curl_easy_setopt(Curl->Handle, CURLOPT_HEADERDATA, State);
		break;
	case CURLOPT_READFUNCTION:
		State->Write = 1;
		curl_easy_setopt(Curl->Handle, CURLOPT_READFUNCTION, function_callback);
		curl_easy_setopt(Curl->Handle, CURLOPT_READDATA, State);
		break;
	default:
		ML_ERROR("CurlError", "Unsupported option for callback");
	}
	ML_RETURN(Curl);
}

ML_METHODX("perform", CurlT) {
	curl_t *Curl = (curl_t *)Args[0];
	curl_easy_perform(Curl->Handle);
	ML_RETURN(Curl);
}

static void nop_free(void *Ptr) {}

static void *GC_calloc(size_t N, size_t S) {
	return GC_malloc(N * S);
}

void ml_library_entry0(ml_value_t **Slot) {
	curl_global_init_mem(CURL_GLOBAL_DEFAULT,
		GC_malloc, nop_free, GC_realloc,
		GC_strdup, GC_calloc
	);
#include "curl_init.c"
	stringmap_insert(CurlT->Exports, "option", CurlOptionT);
	Slot[0] = (ml_value_t *)CurlT;
}

