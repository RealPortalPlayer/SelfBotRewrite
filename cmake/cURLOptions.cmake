set(BUILD_CURL_EXE OFF)
set(BUILD_LIBCURL_DOCS OFF)
set(BUILD_MISC_DOCS OFF)
set(BUILD_SHARED_LIBS OFF)
set(BUILD_STATIC_CURL ON)
set(BUILD_STATIC_LIBS ON)
set(BUILD_TESTING OFF)
set(CURL_DISABLE_ALTSVC ON)
set(CURL_DISABLE_AWS ON)
set(CURL_DISABLE_BASIC_AUTH ON)
set(CURL_DISABLE_BINDLOCAL ON)
set(CURL_DISABLE_DIGEST_AUTH ON)
set(CURL_DISABLE_FILE ON)
set(CURL_DISABLE_FTP ON)
set(CURL_DISABLE_GOPHER ON)
set(CURL_DISABLE_HTTP_AUTH ON)
set(CURL_DISABLE_IMAP ON)
set(CURL_DISABLE_INSTALL ON)
set(CURL_DISABLE_KERBEROS_AUTH ON)
set(CURL_DISABLE_LDAP ON)
set(CURL_DISABLE_LDAPS ON)
set(CURL_DISABLE_MQTT ON)
set(CURL_DISABLE_NEGOTIATE_AUTH ON)
set(CURL_DISABLE_NETRC ON)
set(CURL_DISABLE_NTLM ON)
set(CURL_DISABLE_POP3 ON)
set(CURL_DISABLE_RTSP ON)
set(CURL_DISABLE_SMB ON)
set(CURL_DISABLE_SMTP ON)
set(CURL_DISABLE_SRP ON)
set(CURL_DISABLE_TELNET ON)
set(CURL_DISABLE_TFTP ON)
set(ENABLE_CURL_MANUAL OFF)
set(ENABLE_IPV6 OFF)
set(ENABLE_WEBSOCKETS ON)
set(CURL_USE_LIBSSH2 OFF)
set(CURL_USE_LIBPSL OFF)
set(CURL_ZLIB OFF)
set(USE_LIBIDN2 OFF)

if(WIN32)
    set(USE_WINDOWS_SSPI ON)
    set(USE_SCHANNEL ON)
endif()