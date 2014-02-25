#ifndef _HTTP_PROTOCOL_H
#define _HTTP_PROTOCOL_H

#include <string>

enum HttpMethod{
	HttpGet,
	HttpPost
};

enum HttpResponseCode{
	/* 1xx Infomational */
	StatusContinue = 100,
	StatusSwichingProtocols,

	/* 2xx Succesful */
	StatusOk = 200,
	StatsuCreated,
	StatusAccepted,
	StatusNonAuthorizedInformation,
	StatusNoContent,
	StatusResetContent,
	StatusPartialContent,

	/* 3xx Redirection */
	StatusMultipleChoices = 300,
	StatusMovedPermanetly,
	StatusFound,
	StatusSeeOther,
	StatusNotModified,
	StatusUseProxy,
	StatusTemporaryRedirection = 307,

	/* 4xx Client Error */
	StatusBadRequest = 400,
	StatusUnauthorized,
	StatusPaymentRequired,
	StatusForbidden,
	StatusNotFound,
	StatusMethodNotAllowed,
	StatusNotAcceptable,
	StatusProxyAuthenticationRequired,
	StatusRequestTimeOut,
	StatusConflict,
	StatusGone,
	StatusLengthRequired,
	StatusProconditionFailed,
	StatusRequestEntityTooLarge,
	StatusRequestURITooLarge,
	StatusUnsupportedMediaType,
	StatusRequestedRangeNotSatisfiable,
	StatusExpectationFailed,

	/* 5xx Server Error */
	StatusInternalServerError = 500,
	StatusNotImplemented,
	StatusBadGateway,
	StatusServiceUnavaliable,
	StatusGatewayTimeOut,
	StatusHttpVersionNotSupported
};

const std::string HttpVersion10 = "HTTP/1.0";
const std::string HttpVersion11 = "HTTP/1.1";

#endif //_HTTP_PROTOCOL_H