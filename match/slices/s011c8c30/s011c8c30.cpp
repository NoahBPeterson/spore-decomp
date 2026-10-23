/* Slice s011c8c30 -- OpenSSL 0.9.8g (the lib_cblock copy Spore statically linked).
 *
 * Eight functions from four upstream translation units, compiled verbatim as C
 * (/TC) with the same configuration as the rest of the vendored OpenSSL build
 * (opensslconf.h defines OPENSSL_NO_ERR, so every *err() macro expands to
 * ERR_put_error(lib, func, reason, NULL, 0) -- exactly what the original bytes
 * show).
 *
 *   0x011c8c30  UI_set_result                crypto/ui/ui_lib.c
 *   0x011c8e10  UI_new                       crypto/ui/ui_lib.c
 *   0x011c8e80  ASN1_GENERALIZEDTIME_check   crypto/asn1/a_gentm.c
 *   0x011c8ff0  ASN1_GENERALIZEDTIME_set     crypto/asn1/a_gentm.c
 *   0x011c90e0  ASN1_UTCTIME_check           crypto/asn1/a_utctm.c
 *   0x011c9210  ASN1_UTCTIME_set             crypto/asn1/a_utctm.c
 *   0x011c9330  ec_pre_comp_new              crypto/ec/ec_mult.c
 *   0x011c9490  compute_wNAF                 crypto/ec/ec_mult.c
 *
 * 0x011c8e10 is UI_new, not UI_new_method: the original has UI_new_method(NULL)
 * inlined (there is no branch on the method argument) and UI_get_default_method
 * inlined into it, so the body below is the folded form the compiler produced.
 *
 * Two details of the original codegen are reproduced deliberately:
 *  - CRYPTO_malloc records its caller's __LINE__ as an immediate.  The #line
 *    directives set the line numbers the upstream translation units had
 *    (ui_lib.c:80, a_utctm.c:206, a_gentm.c:226) so those immediates match.
 *  - ec_pre_comp_new and compute_wNAF are file-local statics whose arguments
 *    arrive in registers (EDI) -- a per-translation-unit cl 15.00 convention for
 *    statics.  That only reproduces when the whole ec_mult.c TU is present, so
 *    it is #included below rather than transcribed (as in slice s011cae60).
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include <openssl/bio.h>
#include <openssl/bn.h>
#include <openssl/buffer.h>
#include <openssl/ec.h>
#include <openssl/err.h>
#include <openssl/ui.h>

#include "ui_locl.h"

/* cryptlib.h */
#define DECIMAL_SIZE(type)	((sizeof(type)*8+2)/3+1)

/* crypto/o_time.h (a source-local header) */
struct tm *OPENSSL_gmtime(const time_t *timer, struct tm *result);

/* crypto/ui/ui_lib.c, file-scope */
static const UI_METHOD *default_UI_meth=NULL;


// @ 0x011c8c30  UI_set_result
int UI_set_result(UI *ui, UI_STRING *uis, const char *result)
	{
	int l = strlen(result);

	ui->flags &= ~UI_FLAG_REDOABLE;

	if (!uis)
		return -1;
	switch (uis->type)
		{
	case UIT_PROMPT:
	case UIT_VERIFY:
		{
		char number1[DECIMAL_SIZE(uis->_.string_data.result_minsize)+1];
		char number2[DECIMAL_SIZE(uis->_.string_data.result_maxsize)+1];

		BIO_snprintf(number1, sizeof(number1), "%d",
			uis->_.string_data.result_minsize);
		BIO_snprintf(number2, sizeof(number2), "%d",
			uis->_.string_data.result_maxsize);

		if (l < uis->_.string_data.result_minsize)
			{
			ui->flags |= UI_FLAG_REDOABLE;
			UIerr(UI_F_UI_SET_RESULT,UI_R_RESULT_TOO_SMALL);
			ERR_add_error_data(5,"You must type in ",
				number1," to ",number2," characters");
			return -1;
			}
		if (l > uis->_.string_data.result_maxsize)
			{
			ui->flags |= UI_FLAG_REDOABLE;
			UIerr(UI_F_UI_SET_RESULT,UI_R_RESULT_TOO_LARGE);
			ERR_add_error_data(5,"You must type in ",
				number1," to ",number2," characters");
			return -1;
			}
		}

		if (!uis->result_buf)
			{
			UIerr(UI_F_UI_SET_RESULT,UI_R_NO_RESULT_BUFFER);
			return -1;
			}

		BUF_strlcpy(uis->result_buf, result,
			    uis->_.string_data.result_maxsize + 1);
		break;
	case UIT_BOOLEAN:
		{
		const char *p;

		if (!uis->result_buf)
			{
			UIerr(UI_F_UI_SET_RESULT,UI_R_NO_RESULT_BUFFER);
			return -1;
			}

		uis->result_buf[0] = '\0';
		for(p = result; *p; p++)
			{
			if (strchr(uis->_.boolean_data.ok_chars, *p))
				{
				uis->result_buf[0] =
					uis->_.boolean_data.ok_chars[0];
				break;
				}
			if (strchr(uis->_.boolean_data.cancel_chars, *p))
				{
				uis->result_buf[0] =
					uis->_.boolean_data.cancel_chars[0];
				break;
				}
			}
	default:
		break;
		}
		}
	return 0;
	}


#line 75
// @ 0x011c8e10  UI_new
UI *UI_new(void)
	{
	UI *ret;

	ret=(UI *)OPENSSL_malloc(sizeof(UI));
	if (ret == NULL)
		{
		UIerr(UI_F_UI_NEW_METHOD,ERR_R_MALLOC_FAILURE);
		return NULL;
		}
	if (default_UI_meth == NULL)
		default_UI_meth = UI_OpenSSL();
	ret->meth = default_UI_meth;
	ret->strings=NULL;
	ret->user_data=NULL;
	CRYPTO_new_ex_data(CRYPTO_EX_INDEX_UI, ret, &ret->ex_data);
	return ret;
	}


// @ 0x011c8e80  ASN1_GENERALIZEDTIME_check
int ASN1_GENERALIZEDTIME_check(ASN1_GENERALIZEDTIME *d)
	{
	static int min[9]={ 0, 0, 1, 1, 0, 0, 0, 0, 0};
	static int max[9]={99, 99,12,31,23,59,59,12,59};
	char *a;
	int n,i,l,o;

	if (d->type != V_ASN1_GENERALIZEDTIME) return(0);
	l=d->length;
	a=(char *)d->data;
	o=0;
	/* GENERALIZEDTIME is similar to UTCTIME except the year is
         * represented as YYYY. This stuff treats everything as a two digit
         * field so make first two fields 00 to 99
         */
	if (l < 13) goto err;
	for (i=0; i<7; i++)
		{
		if ((i == 6) && ((a[o] == 'Z') ||
			(a[o] == '+') || (a[o] == '-')))
			{ i++; break; }
		if ((a[o] < '0') || (a[o] > '9')) goto err;
		n= a[o]-'0';
		if (++o > l) goto err;

		if ((a[o] < '0') || (a[o] > '9')) goto err;
		n=(n*10)+ a[o]-'0';
		if (++o > l) goto err;

		if ((n < min[i]) || (n > max[i])) goto err;
		}
	/* Optional fractional seconds: decimal point followed by one
	 * or more digits.
	 */
	if (a[o] == '.')
		{
		if (++o > l) goto err;
		i = o;
		while ((a[o] >= '0') && (a[o] <= '9') && (o <= l))
			o++;
		/* Must have at least one digit after decimal point */
		if (i == o) goto err;
		}

	if (a[o] == 'Z')
		o++;
	else if ((a[o] == '+') || (a[o] == '-'))
		{
		o++;
		if (o+4 > l) goto err;
		for (i=7; i<9; i++)
			{
			if ((a[o] < '0') || (a[o] > '9')) goto err;
			n= a[o]-'0';
			o++;
			if ((a[o] < '0') || (a[o] > '9')) goto err;
			n=(n*10)+ a[o]-'0';
			if ((n < min[i]) || (n > max[i])) goto err;
			o++;
			}
		}
	return(o == l);
err:
	return(0);
	}


#line 205
// @ 0x011c8ff0  ASN1_GENERALIZEDTIME_set
ASN1_GENERALIZEDTIME *ASN1_GENERALIZEDTIME_set(ASN1_GENERALIZEDTIME *s,
	     time_t t)
	{
	char *p;
	struct tm *ts;
	struct tm data;
	size_t len = 20; 

	if (s == NULL)
		s=M_ASN1_GENERALIZEDTIME_new();
	if (s == NULL)
		return(NULL);

	ts=OPENSSL_gmtime(&t, &data);
	if (ts == NULL)
		return(NULL);

	p=(char *)s->data;
	if ((p == NULL) || ((size_t)s->length < len))
		{
		p=OPENSSL_malloc(len);
		if (p == NULL)
			{
			ASN1err(ASN1_F_ASN1_GENERALIZEDTIME_SET,
				ERR_R_MALLOC_FAILURE);
			return(NULL);
			}
		if (s->data != NULL)
			OPENSSL_free(s->data);
		s->data=(unsigned char *)p;
		}

	BIO_snprintf(p,len,"%04d%02d%02d%02d%02d%02dZ",ts->tm_year + 1900,
		     ts->tm_mon+1,ts->tm_mday,ts->tm_hour,ts->tm_min,ts->tm_sec);
	s->length=strlen(p);
	s->type=V_ASN1_GENERALIZEDTIME;
#ifdef CHARSET_EBCDIC_not
	ebcdic2ascii(s->data, s->data, s->length);
#endif
	return(s);
	}


// @ 0x011c90e0  ASN1_UTCTIME_check
int ASN1_UTCTIME_check(ASN1_UTCTIME *d)
	{
	static int min[8]={ 0, 1, 1, 0, 0, 0, 0, 0};
	static int max[8]={99,12,31,23,59,59,12,59};
	char *a;
	int n,i,l,o;

	if (d->type != V_ASN1_UTCTIME) return(0);
	l=d->length;
	a=(char *)d->data;
	o=0;

	if (l < 11) goto err;
	for (i=0; i<6; i++)
		{
		if ((i == 5) && ((a[o] == 'Z') ||
			(a[o] == '+') || (a[o] == '-')))
			{ i++; break; }
		if ((a[o] < '0') || (a[o] > '9')) goto err;
		n= a[o]-'0';
		if (++o > l) goto err;

		if ((a[o] < '0') || (a[o] > '9')) goto err;
		n=(n*10)+ a[o]-'0';
		if (++o > l) goto err;

		if ((n < min[i]) || (n > max[i])) goto err;
		}
	if (a[o] == 'Z')
		o++;
	else if ((a[o] == '+') || (a[o] == '-'))
		{
		o++;
		if (o+4 > l) goto err;
		for (i=6; i<8; i++)
			{
			if ((a[o] < '0') || (a[o] > '9')) goto err;
			n= a[o]-'0';
			o++;
			if ((a[o] < '0') || (a[o] > '9')) goto err;
			n=(n*10)+ a[o]-'0';
			if ((n < min[i]) || (n > max[i])) goto err;
			o++;
			}
		}
	return(o == l);
err:
	return(0);
	}


#line 186
// @ 0x011c9210  ASN1_UTCTIME_set
ASN1_UTCTIME *ASN1_UTCTIME_set(ASN1_UTCTIME *s, time_t t)
	{
	char *p;
	struct tm *ts;
	struct tm data;
	size_t len = 20;

	if (s == NULL)
		s=M_ASN1_UTCTIME_new();
	if (s == NULL)
		return(NULL);

	ts=OPENSSL_gmtime(&t, &data);
	if (ts == NULL)
		return(NULL);

	p=(char *)s->data;
	if ((p == NULL) || ((size_t)s->length < len))
		{
		p=OPENSSL_malloc(len);
		if (p == NULL)
			{
			ASN1err(ASN1_F_ASN1_UTCTIME_SET,ERR_R_MALLOC_FAILURE);
			return(NULL);
			}
		if (s->data != NULL)
			OPENSSL_free(s->data);
		s->data=(unsigned char *)p;
		}

	BIO_snprintf(p,len,"%02d%02d%02d%02d%02d%02dZ",ts->tm_year%100,
		     ts->tm_mon+1,ts->tm_mday,ts->tm_hour,ts->tm_min,ts->tm_sec);
	s->length=strlen(p);
	s->type=V_ASN1_UTCTIME;
#ifdef CHARSET_EBCDIC_not
	ebcdic2ascii(s->data, s->data, s->length);
#endif
	return(s);
	}


/* The two file-local statics of crypto/ec/ec_mult.c arrive with their
 * arguments in EDI (see the header comment), which cl 15.00 only produces when
 * the whole translation unit is compiled; include it verbatim. */
// @ 0x011c9330  ec_pre_comp_new
// @ 0x011c9490  compute_wNAF
#include "../../../work/third_party/build/openssl-0.9.8g-d2110920/crypto/ec/ec_mult.c"
