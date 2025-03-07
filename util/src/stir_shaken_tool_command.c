#include <stir_shaken_tool.h>


int stirshaken_command_configure(stir_shaken_context_t *ss, const char *command_name, struct ca *ca, struct pa *pa, struct sp *sp, struct options *options)
{
	if (!command_name || !options) {
		return COMMAND_UNKNOWN;
	}

	if (!strcmp(command_name, COMMAND_NAME_KEYS)) {

		return COMMAND_KEYS;

	} else if (!strcmp(command_name, COMMAND_NAME_CSR)) {

		strncpy(sp->spc, options->spc, STIR_SHAKEN_BUFLEN);
		strncpy(sp->sp.csr_name, options->file, STIR_SHAKEN_BUFLEN);
		strncpy(sp->sp.public_key_name, options->public_key_name, STIR_SHAKEN_BUFLEN);
		strncpy(sp->sp.private_key_name, options->private_key_name, STIR_SHAKEN_BUFLEN);
		strncpy(sp->subject_c, options->subject_c, STIR_SHAKEN_BUFLEN);
		strncpy(sp->subject_cn, options->subject_cn, STIR_SHAKEN_BUFLEN);
		return COMMAND_CSR;

	} else if (!strcmp(command_name, COMMAND_NAME_CERT)) {

		if (COMMAND_CERT_CA == options->command_cert_type) {

			strncpy(ca->ca.cert_name, options->file, STIR_SHAKEN_BUFLEN);
			strncpy(ca->ca.issuer_c, options->issuer_c, STIR_SHAKEN_BUFLEN);
			strncpy(ca->ca.issuer_cn, options->issuer_cn, STIR_SHAKEN_BUFLEN);
			strncpy(ca->ca.public_key_name, options->public_key_name, STIR_SHAKEN_BUFLEN);
			strncpy(ca->ca.private_key_name, options->private_key_name, STIR_SHAKEN_BUFLEN);
			ca->ca.expiry_days = options->expiry_days;
			ca->ca.serial = options->serial;
			return COMMAND_CERT_CA;

		} else if (COMMAND_CERT_SP == options->command_cert_type) {

			strncpy(ca->ca.public_key_name, options->public_key_name, STIR_SHAKEN_BUFLEN);
			strncpy(ca->ca.private_key_name, options->private_key_name, STIR_SHAKEN_BUFLEN);
			strncpy(sp->sp.csr_name, options->csr_name, STIR_SHAKEN_BUFLEN);
			strncpy(ca->ca.cert_name, options->ca_cert, STIR_SHAKEN_BUFLEN);
			strncpy(sp->sp.cert_name, options->file, STIR_SHAKEN_BUFLEN);
			strncpy(ca->ca.issuer_c, options->issuer_c, STIR_SHAKEN_BUFLEN);
			strncpy(ca->ca.issuer_cn, options->issuer_cn, STIR_SHAKEN_BUFLEN);
			strncpy(ca->ca.tn_auth_list_uri, options->tn_auth_list_uri, STIR_SHAKEN_BUFLEN);
			ca->ca.expiry_days = options->expiry_days;
			ca->ca.serial = options->serial;
			return COMMAND_CERT_SP;

		} else {
			stir_shaken_set_error(ss, "Bad --type", STIR_SHAKEN_ERROR_GENERAL);
			return COMMAND_UNKNOWN;
		}

	} else if (!strcmp(command_name, COMMAND_NAME_HASH_CERT)) {

		strncpy(ca->ca.cert_name, options->file, STIR_SHAKEN_BUFLEN);
		return COMMAND_HASH_CERT;

	} else if (!strcmp(command_name, COMMAND_NAME_SPC_TOKEN)) {

		strncpy(pa->spc, options->spc, STIR_SHAKEN_BUFLEN);
		strncpy(pa->pa.private_key_name, options->private_key_name, STIR_SHAKEN_BUFLEN);
		strncpy(pa->issuer_cn, options->issuer_cn, STIR_SHAKEN_BUFLEN);
		strncpy(pa->url, options->url, STIR_SHAKEN_BUFLEN);
		strncpy(pa->file_name, options->file, STIR_SHAKEN_BUFLEN);
		return COMMAND_SPC_TOKEN;

	} else if (!strcmp(command_name, COMMAND_NAME_CA)) {

		ca->ca.port = options->port;
		strncpy(ca->ca.private_key_name, options->private_key_name, STIR_SHAKEN_BUFLEN);
		strncpy(ca->ca.cert_name, options->ca_cert, STIR_SHAKEN_BUFLEN);
		ca->ca.use_ssl = options->use_ssl;
		strncpy(ca->ca.ssl_cert_name, options->ssl_cert_name, STIR_SHAKEN_BUFLEN);
		strncpy(ca->ca.ssl_key_name, options->ssl_key_name, STIR_SHAKEN_BUFLEN);
		strncpy(ca->ca.issuer_c, options->issuer_c, STIR_SHAKEN_BUFLEN);
		strncpy(ca->ca.issuer_cn, options->issuer_cn, STIR_SHAKEN_BUFLEN);
		strncpy(ca->ca.tn_auth_list_uri, options->tn_auth_list_uri, STIR_SHAKEN_BUFLEN);
		ca->ca.expiry_days = options->expiry_days;
		ca->ca.serial = options->serial;
		strncpy(ca->ca.trusted_pa_cert_name, options->pa_cert, STIR_SHAKEN_BUFLEN);
		ca->ca.use_trusted_pa_hash = stir_shaken_zstr(ca->ca.trusted_pa_cert_name) ? 0 : 1;
		strncpy(ca->ca.pa_dir_name, options->pa_dir_name, STIR_SHAKEN_BUFLEN);
		ca->ca.use_pa_dir = stir_shaken_zstr(ca->ca.pa_dir_name) ? 0 : 1;
		return COMMAND_CA;

	} else if (!strcmp(command_name, COMMAND_NAME_PA)) {

		pa->pa.port = options->port;
		return COMMAND_PA;

	} else if (!strcmp(command_name, COMMAND_NAME_SP_SPC_REQ)) {

		strncpy(sp->url, options->url, STIR_SHAKEN_BUFLEN);
		return COMMAND_SP_SPC_REQ;

	} else if (!strcmp(command_name, COMMAND_NAME_SP_CERT_REQ)) {

		sp->sp.port = options->port;
		strncpy(sp->spc, options->spc, STIR_SHAKEN_BUFLEN);
		strncpy(sp->sp.spc_token, options->spc_token, STIR_SHAKEN_BUFLEN);
		strncpy(sp->url, options->url, STIR_SHAKEN_BUFLEN);
		strncpy(sp->sp.public_key_name, options->public_key_name, STIR_SHAKEN_BUFLEN);
		strncpy(sp->sp.private_key_name, options->private_key_name, STIR_SHAKEN_BUFLEN);
		strncpy(sp->sp.csr_name, options->csr_name, STIR_SHAKEN_BUFLEN);
		strncpy(sp->sp.cert_name, options->file, STIR_SHAKEN_BUFLEN);
		return COMMAND_SP_CERT_REQ;

	} else if (!strcmp(command_name, COMMAND_NAME_JWT_KEY_CHECK)) {
		return COMMAND_JWT_KEY_CHECK;

	} else if (!strcmp(command_name, COMMAND_NAME_JWT_CHECK)) {
		return COMMAND_JWT_CHECK;

	} else if (!strcmp(command_name, COMMAND_NAME_JWT_DUMP)) {
		return COMMAND_JWT_DUMP;

	} else if (!strcmp(command_name, COMMAND_NAME_PASSPORT_CREATE)) {
		memcpy(&sp->sp.passport_params, &options->passport_params, sizeof(sp->sp.passport_params));
		sp->sp.passport_params.x5u = strdup(options->url);
		sp->sp.passport_params.iat = time(NULL);
		//strncpy(sp->sp.passport_params.origtn, options->passport_params.origtn, STIR_SHAKEN_BUFLEN);
		//strncpy(sp->sp.passport_params.desttn, options->passport_params.desttn, STIR_SHAKEN_BUFLEN);
		//strncpy(sp->sp.passport_params.origid, options->passport_params.origid, STIR_SHAKEN_BUFLEN);
		return COMMAND_PASSPORT_CREATE;

	} else if (!strcmp(command_name, COMMAND_NAME_VERSION)) {
		return COMMAND_VERSION;

	} else {

		stir_shaken_set_error(ss, "Unknown command", STIR_SHAKEN_ERROR_GENERAL);
		return COMMAND_UNKNOWN;
	}
}

stir_shaken_status_t stirshaken_command_validate(stir_shaken_context_t *ss, int command, struct ca *ca, struct pa *pa, struct sp *sp, struct options *options)
{
	unsigned long long helper = 0;
	char *pCh = NULL;

	switch (command) {

		case COMMAND_KEYS:

			if (stir_shaken_zstr(options->private_key_name)) {
				fprintf(stderr, "ERROR: private key parameter missing\n");
				goto fail;
			}

			if (stir_shaken_zstr(options->public_key_name)) {
				fprintf(stderr, "ERROR: public key parameter missing\n");
				goto fail;
			}

			if (STIR_SHAKEN_STATUS_OK == stir_shaken_file_exists(options->private_key_name)) {
				fprintf(stderr, "ERROR: File %s exists...\nPlease remove it or use different.\n\n", options->private_key_name);
				goto fail;
			}

			if (STIR_SHAKEN_STATUS_OK == stir_shaken_file_exists(options->public_key_name)) {
				fprintf(stderr, "ERROR: File %s exists...\nPlease remove it or use different.\n\n", options->public_key_name);
				goto fail;
			}

			break;

		case COMMAND_CSR:

			if (stir_shaken_zstr(sp->sp.private_key_name) || stir_shaken_zstr(sp->sp.public_key_name)
					|| stir_shaken_zstr(sp->subject_c) || stir_shaken_zstr(sp->subject_cn)
					|| stir_shaken_zstr(sp->spc) || stir_shaken_zstr(sp->sp.csr_name)) {
				fprintf(stderr, "ERROR: CSR parameters missing\n");
				goto fail;
			}

			if (STIR_SHAKEN_STATUS_OK == stir_shaken_file_exists(sp->sp.csr_name)) {
				fprintf(stderr, "ERROR: File %s exists...\nPlease remove it or use different.\n\n", sp->sp.csr_name);
				goto fail;
			}

            strcpy(pa->sp_code, sp->spc);

            break;

		case COMMAND_CERT_CA:

			if (stir_shaken_zstr(ca->ca.cert_name) || stir_shaken_zstr(ca->ca.private_key_name) || stir_shaken_zstr(ca->ca.public_key_name)
					|| stir_shaken_zstr(ca->ca.issuer_c) || stir_shaken_zstr(ca->ca.issuer_cn) || ca->ca.expiry_days == 0 || ca->ca.serial == 0) {
				fprintf(stderr, "ERROR: CA parameters missing\n");
				goto fail;
			}

			if (STIR_SHAKEN_STATUS_OK == stir_shaken_file_exists(ca->ca.cert_name)) {
				fprintf(stderr, "ERROR: File %s exists...\nPlease remove it or use different.\n\n", ca->ca.cert_name);
				goto fail;
			}
			break;

		case COMMAND_CERT_SP:

			if (stir_shaken_zstr(sp->sp.cert_name) || stir_shaken_zstr(ca->ca.private_key_name) || stir_shaken_zstr(ca->ca.public_key_name)
					|| stir_shaken_zstr(sp->sp.csr_name) || stir_shaken_zstr(ca->ca.cert_name)
					|| stir_shaken_zstr(ca->ca.issuer_c) || stir_shaken_zstr(ca->ca.issuer_cn) || stir_shaken_zstr(ca->ca.tn_auth_list_uri) || ca->ca.expiry_days == 0 || ca->ca.serial == 0) {
				fprintf(stderr, "ERROR: SP parameters missing\n");
				goto fail;
			}

			if (STIR_SHAKEN_STATUS_OK == stir_shaken_file_exists(sp->sp.cert_name)) {
				fprintf(stderr, "ERROR: File %s exists...\nPlease remove it or use different.\n\n", sp->sp.cert_name);
				goto fail;
			}
			break;

		case COMMAND_HASH_CERT:

			if (stir_shaken_zstr(ca->ca.cert_name)) {
				fprintf(stderr, "ERROR: CA cert name missing\n");
				goto fail;
			}

			if (STIR_SHAKEN_STATUS_OK != stir_shaken_file_exists(ca->ca.cert_name)) {
				fprintf(stderr, "ERROR: File %s does not exist.\n\n", ca->ca.cert_name);
				goto fail;
			}
			break;

		case COMMAND_SPC_TOKEN:

			if (stir_shaken_zstr(pa->pa.private_key_name) || stir_shaken_zstr(pa->issuer_cn) || stir_shaken_zstr(pa->spc) || stir_shaken_zstr(pa->url)) {
				fprintf(stderr, "ERROR: PA parameters missing\n");
				goto fail;
			}

			if (STIR_SHAKEN_STATUS_OK == stir_shaken_file_exists(pa->file_name)) {
				fprintf(stderr, "ERROR: File %s exists...\nPlease remove it or use different.\n\n", pa->file_name);
				goto fail;
			}

            strcpy(pa->sp_code, sp->spc);

            break;

		case COMMAND_CA:

			if (stir_shaken_zstr(ca->ca.private_key_name) || stir_shaken_zstr(ca->ca.cert_name) || stir_shaken_zstr(ca->ca.issuer_c) || stir_shaken_zstr(ca->ca.issuer_cn) || stir_shaken_zstr(ca->ca.tn_auth_list_uri) || ca->ca.serial == 0) {
				fprintf(stderr, "ERROR: CA parameters missing\n");
				goto fail;
			}

			if (ca->ca.use_ssl && stir_shaken_zstr(ca->ca.ssl_cert_name)) {
				fprintf(stderr, "ERROR: SSL cannot be started because cert is missing (please specify ssl certificate with --%s argument)\n\n", OPTION_NAME_SSL_CERT);
				goto fail;
			}

			if (ca->ca.use_ssl && stir_shaken_zstr(ca->ca.ssl_key_name)) {
				fprintf(stderr, "ERROR: SSL cannot be started because key is missing (please specify ssl key with --%s argument)\n\n", OPTION_NAME_SSL_KEY);
				goto fail;
			}

			if (ca->ca.use_trusted_pa_hash ^ !stir_shaken_zstr(ca->ca.trusted_pa_cert_name)) {
				fprintf(stderr, "ERROR: trusted PA certificate is missing\n");
				goto fail;
			}

			if (ca->ca.use_pa_dir ^ !stir_shaken_zstr(ca->ca.pa_dir_name)) {
				fprintf(stderr, "ERROR: trusted PA roots folder is missing\n");
				goto fail;
			}
			break;

		case COMMAND_PA:
			break;

		case COMMAND_SP_SPC_REQ:

			if (stir_shaken_zstr(sp->url)) {
				fprintf(stderr, "ERROR: URL missing\n");
				goto fail;
			}
			break;

		case COMMAND_SP_CERT_REQ:

			if (stir_shaken_zstr(sp->sp.cert_name) || stir_shaken_zstr(sp->url) || stir_shaken_zstr(sp->sp.private_key_name) || stir_shaken_zstr(sp->sp.public_key_name)
					|| stir_shaken_zstr(sp->spc) || stir_shaken_zstr(sp->sp.spc_token) || stir_shaken_zstr(sp->sp.csr_name)) {
				fprintf(stderr, "ERROR: SP parameters missing\n");
				goto fail;
			}

            strcpy(pa->sp_code, sp->spc);

            break;


		case COMMAND_JWT_KEY_CHECK:

			if (stir_shaken_zstr(options->public_key_name)) {
				fprintf(stderr, "ERROR: public key name missing\n");
				goto fail;
			}

			if (stir_shaken_zstr(options->jwt)) {
				fprintf(stderr, "ERROR: JWT missing\n");
				goto fail;
			}
			break;

		case COMMAND_JWT_CHECK:

			if (stir_shaken_zstr(options->jwt)) {
				goto fail;
			}

			if (options->x509_cert_path_check) {
				if (stir_shaken_zstr(options->ca_dir_name)) {
					fprintf(stderr, "ERROR: X509 cert path check is turned on but CA dir missing. Add --%s?\n", OPTION_NAME_CA_DIR);
					goto fail;
				}

				if (STIR_SHAKEN_STATUS_OK != stir_shaken_dir_exists(options->ca_dir_name)) {
					fprintf(stderr, "ERROR: Directory %s does not exist\n", options->ca_dir_name);
					goto fail;
				}
			}

			break;

		case COMMAND_JWT_DUMP:

			if (stir_shaken_zstr(options->jwt)) {
				fprintf(stderr, "ERROR: JWT missing\n");
				goto fail;
			}
			break;

		case COMMAND_PASSPORT_CREATE:

			if (stir_shaken_zstr(options->private_key_name)) {
				fprintf(stderr, "ERROR: private key name missing\n");
				goto fail;
			}

			if (stir_shaken_zstr(options->url)) {
				fprintf(stderr, "ERROR: cert URL missing\n");
				goto fail;
			}

			if (stir_shaken_zstr(sp->sp.passport_params.origtn_val)) {
				fprintf(stderr, "ERROR: PASSporT's origtn param missing\n");
				goto fail;
			}

			if (stir_shaken_zstr(sp->sp.passport_params.desttn_val)) {
				fprintf(stderr, "ERROR: PASSporT's desttn param missing\n");
				goto fail;
			}

			if (stir_shaken_zstr(sp->sp.passport_params.origid)) {
				fprintf(stderr, "ERROR: PASSporT's origid param missing\n");
				goto fail;
			}

			if (stir_shaken_zstr(options->file)) {
				fprintf(stderr, "ERROR: output file name missing\n");
				goto fail;
			}

			if (STIR_SHAKEN_STATUS_OK != stir_shaken_file_exists(options->private_key_name)) {
				fprintf(stderr, "ERROR: File %s does not exist.\n\n", options->private_key_name);
				goto fail;
			}

			if (STIR_SHAKEN_STATUS_OK == stir_shaken_file_exists(options->file)) {
				fprintf(stderr, "ERROR: File %s exists...\nPlease remove it or use different.\n\n", options->file);
				goto fail;
			}
			break;

		case COMMAND_VERSION:
			break;

		case COMMAND_CERT:
		case COMMAND_UNKNOWN:
		default:
			goto fail;
	}

	return STIR_SHAKEN_STATUS_OK;

fail:
	return STIR_SHAKEN_STATUS_FALSE;
}

stir_shaken_status_t stirshaken_command_execute(stir_shaken_context_t *ss, int command, struct ca *ca, struct pa *pa, struct sp *sp, struct options *options)
{
	stir_shaken_status_t status = STIR_SHAKEN_STATUS_OK;
	unsigned long	hash = 0;
	char			hashstr[100] = { 0 };
	int				hashstrlen = 100;
	char			*spc_token_encoded = NULL;
	char			*spc_token_decoded = NULL;
	char			token[STIR_SHAKEN_BUFLEN] = { 0 };
	jwt_t			*jwt = NULL;
	char            *jwt_decoded = NULL;
	stir_shaken_cert_t *cert = NULL;
	char *p1 = NULL, *p2 = NULL, *sih = NULL;
	stir_shaken_passport_t *passport = NULL;
	stir_shaken_vs_t *vs = NULL;


	if (STIR_SHAKEN_STATUS_OK != stir_shaken_init(ss, options->loglevel)) {
		goto fail;
	}

	switch (command) {

		case COMMAND_KEYS:

			status = stir_shaken_generate_keys(ss, &options->keys.ec_key, &options->keys.private_key, &options->keys.public_key, options->private_key_name, options->public_key_name, NULL, NULL);
			if (STIR_SHAKEN_STATUS_OK != status) {
				goto fail;
			}
			break;

		case COMMAND_CSR:

			fprintif(STIR_SHAKEN_LOGLEVEL_BASIC, "Loading keys...\n");
			if (STIR_SHAKEN_STATUS_OK != stir_shaken_load_keys(ss, &sp->sp.keys.private_key, &sp->sp.keys.public_key, sp->sp.private_key_name, sp->sp.public_key_name, NULL, NULL)) {
				goto fail;
			}

			fprintif(STIR_SHAKEN_LOGLEVEL_BASIC, "Generating CSR...\n");
			if (STIR_SHAKEN_STATUS_OK != stir_shaken_generate_csr(ss, sp->sp.code, &sp->sp.csr.req, sp->sp.keys.private_key, sp->sp.keys.public_key, sp->subject_c, sp->subject_cn)) {
				goto fail;
			}

			fprintif(STIR_SHAKEN_LOGLEVEL_BASIC, "Saving CSR...\n");
			if (STIR_SHAKEN_STATUS_OK != stir_shaken_csr_to_disk(ss, sp->sp.csr.req, sp->sp.csr_name)) {
				goto fail;
			}
			break;

		case COMMAND_CERT_CA:

			fprintif(STIR_SHAKEN_LOGLEVEL_BASIC, "Loading keys...\n");
			if (STIR_SHAKEN_STATUS_OK != stir_shaken_load_keys(ss, &ca->ca.keys.private_key, &ca->ca.keys.public_key, ca->ca.private_key_name, ca->ca.public_key_name, NULL, NULL)) {
				goto fail;
			}

			fprintif(STIR_SHAKEN_LOGLEVEL_BASIC, "Generating cert...\n");
			ca->ca.cert.x = stir_shaken_generate_x509_self_signed_ca_cert(ss, ca->ca.keys.private_key, ca->ca.keys.public_key, ca->ca.issuer_c, ca->ca.issuer_cn, ca->ca.serial, ca->ca.expiry_days);
			if (!ca->ca.cert.x) {
				goto fail;
			}

			fprintif(STIR_SHAKEN_LOGLEVEL_BASIC, "Saving certificate...\n");
			if (STIR_SHAKEN_STATUS_OK != stir_shaken_x509_to_disk(ss, ca->ca.cert.x, ca->ca.cert_name)) {
				goto fail;
			}

			stir_shaken_hash_cert_name(ss, &ca->ca.cert);
			fprintif(STIR_SHAKEN_LOGLEVEL_BASIC, "CA name hash is %lu\n", ca->ca.cert.hash);
			fprintif(STIR_SHAKEN_LOGLEVEL_BASIC, "CA hashed file name is %s\n", ca->ca.cert.cert_name_hashed);

			fprintif(STIR_SHAKEN_LOGLEVEL_BASIC, "Saving certificate under hashed name...\n");
			if (STIR_SHAKEN_STATUS_OK != stir_shaken_x509_to_disk(ss, ca->ca.cert.x, ca->ca.cert.cert_name_hashed)) {
				goto fail;
			}

			break;

		case COMMAND_CERT_SP:

			fprintif(STIR_SHAKEN_LOGLEVEL_BASIC, "Loading keys...\n");
			if (STIR_SHAKEN_STATUS_OK != stir_shaken_load_keys(ss, &ca->ca.keys.private_key, &ca->ca.keys.public_key, ca->ca.private_key_name, ca->ca.public_key_name, NULL, NULL)) {
				goto fail;
			}

			fprintif(STIR_SHAKEN_LOGLEVEL_BASIC, "Loading CSR...\n");
			sp->sp.csr.req = stir_shaken_load_x509_req_from_file(ss, sp->sp.csr_name);
			if (!sp->sp.csr.req) {
				goto fail;
			}

			fprintif(STIR_SHAKEN_LOGLEVEL_BASIC, "Loading CA certificate...\n");
			ca->ca.cert.x = stir_shaken_load_x509_from_file(ss, ca->ca.cert_name);
			if (!ca->ca.cert.x) {
				goto fail;
			}

			fprintif(STIR_SHAKEN_LOGLEVEL_BASIC, "Generating cert...\n");
			sp->sp.cert.x = stir_shaken_generate_x509_end_entity_cert_from_csr(ss, ca->ca.cert.x, ca->ca.keys.private_key, ca->ca.issuer_c, ca->ca.issuer_cn, sp->sp.csr.req, ca->ca.serial, ca->ca.expiry_days, ca->ca.tn_auth_list_uri);
			if (!sp->sp.cert.x) {
				goto fail;
			}

			fprintif(STIR_SHAKEN_LOGLEVEL_BASIC, "Saving certificate...\n");
			if (STIR_SHAKEN_STATUS_OK != stir_shaken_x509_to_disk(ss, sp->sp.cert.x, sp->sp.cert_name)) {
				goto fail;
			}
			break;

		case COMMAND_HASH_CERT:

			fprintif(STIR_SHAKEN_LOGLEVEL_BASIC, "Loading certificate...\n");
			ca->ca.cert.x = stir_shaken_load_x509_from_file(ss, ca->ca.cert_name);
			if (!ca->ca.cert.x) {
				goto fail;
			}

			hash = stir_shaken_get_cert_name_hashed(ss, ca->ca.cert.x);
			if (hash == 0) {
				goto fail;
			}

			fprintif(STIR_SHAKEN_LOGLEVEL_BASIC, "Certificate name hash is %lu\n", hash);
			stir_shaken_cert_name_hashed_2_string(hash, hashstr, hashstrlen);
			sprintf(ca->ca.cert_name_hashed, "%s.0", hashstr);
			fprintif(STIR_SHAKEN_LOGLEVEL_BASIC, "Certificate name hashed is %s\n", ca->ca.cert_name_hashed);

			fprintif(STIR_SHAKEN_LOGLEVEL_BASIC, "Saving certificate as %s...\n", ca->ca.cert_name_hashed);
			if (STIR_SHAKEN_STATUS_OK != stir_shaken_x509_to_disk(ss, ca->ca.cert.x, ca->ca.cert_name_hashed)) {
				goto fail;
			}
			break;

		case COMMAND_SPC_TOKEN:

			fprintif(STIR_SHAKEN_LOGLEVEL_BASIC, "Loading keys...\n");
			pa->pa.keys.priv_raw_len = STIR_SHAKEN_PRIV_KEY_RAW_BUF_LEN;
			if (STIR_SHAKEN_STATUS_OK != stir_shaken_load_keys(ss, &pa->pa.keys.private_key, NULL, pa->pa.private_key_name, NULL, pa->pa.keys.priv_raw, &pa->pa.keys.priv_raw_len)) {
				goto fail;
			}

			// TODO get nb/na from user
			snprintf(pa->nb, STIR_SHAKEN_BUFLEN, "today");
			snprintf(pa->na, STIR_SHAKEN_BUFLEN, "1 year from now");

			fprintif(STIR_SHAKEN_LOGLEVEL_BASIC, "Generating SPC token...\n");
			spc_token_encoded = stir_shaken_acme_generate_spc_token(ss, pa->issuer_cn, pa->url, pa->nb, pa->na, pa->spc, pa->pa.keys.priv_raw, pa->pa.keys.priv_raw_len, &spc_token_decoded);
			if (!spc_token_encoded || !spc_token_decoded) {
				goto fail;
			}

			fprintif(STIR_SHAKEN_LOGLEVEL_BASIC, "\nSPC token encoded:\n\n%s\n", spc_token_encoded);
			fprintif(STIR_SHAKEN_LOGLEVEL_BASIC, "\nSPC token decoded:\n\n%s\n", spc_token_decoded);
			snprintf(token, STIR_SHAKEN_BUFLEN, "SPC token encoded:\n\n%s\n\nSPC token decoded:\n\n%s", spc_token_encoded, spc_token_decoded);

			fprintif(STIR_SHAKEN_LOGLEVEL_BASIC, "Saving...\n");
			if (STIR_SHAKEN_STATUS_OK != stir_shaken_save_to_file(ss, token, pa->file_name)) {
				goto fail;
			}

			free(spc_token_encoded); spc_token_encoded = NULL;
			free(spc_token_decoded); spc_token_decoded = NULL;
			break;

		case COMMAND_CA:

			fprintif(STIR_SHAKEN_LOGLEVEL_BASIC, "Loading keys...\n");
			if (STIR_SHAKEN_STATUS_OK != stir_shaken_load_keys(ss, &ca->ca.keys.private_key, NULL, ca->ca.private_key_name, NULL, NULL, NULL)) {
				goto fail;
			}

			fprintif(STIR_SHAKEN_LOGLEVEL_BASIC, "Loading CA certificate...\n");
			ca->ca.cert.x = stir_shaken_load_x509_from_file(ss, ca->ca.cert_name);
			if (!ca->ca.cert.x) {
				goto fail;
			}

			fprintif(STIR_SHAKEN_LOGLEVEL_BASIC, "Starting CA service...\n");
			if (STIR_SHAKEN_STATUS_OK != stir_shaken_run_ca_service(ss, &ca->ca)) {
				goto fail;
			}
			stir_shaken_ca_destroy(&ca->ca);
			break;

		case COMMAND_SP_SPC_REQ:
			break;

		case COMMAND_SP_CERT_REQ:

			{
				stir_shaken_http_req_t http_req = { 0 };
				char *jwt_encoded = NULL;
				char *jwt_decoded = NULL;
				char spc[STIR_SHAKEN_BUFLEN] = { 0 };

				fprintif(STIR_SHAKEN_LOGLEVEL_BASIC, "Loading keys...\n");
				sp->sp.keys.priv_raw_len = sizeof(sp->sp.keys.priv_raw);
				if (STIR_SHAKEN_STATUS_OK != stir_shaken_load_keys(ss, &sp->sp.keys.private_key, &sp->sp.keys.public_key, sp->sp.private_key_name, sp->sp.public_key_name, sp->sp.keys.priv_raw, &sp->sp.keys.priv_raw_len)) {
					goto fail;
				}

				fprintif(STIR_SHAKEN_LOGLEVEL_BASIC, "Loading CSR...\n");
				sp->sp.csr.req = stir_shaken_load_x509_req_from_file(ss, sp->sp.csr_name);
				if (!sp->sp.csr.req) {
					goto fail;
				}

				fprintif(STIR_SHAKEN_LOGLEVEL_BASIC, "Requesting STI certificate...\n");
				http_req.url = strdup(sp->url);
				http_req.remote_port = sp->sp.port;

				// Can do:
				// status = stir_shaken_sp_cert_req_ex(ss, &http_req, sp->sp.kid, sp->sp.nonce, sp->sp.csr.req, sp->sp.nb, sp->sp.na, sp->sp.keys.priv_raw, sp->sp.keys.priv_raw_len, &jwt_decoded, sp->sp.spc_token);
				//
				// or for explicit JWT:

				sprintf(spc, "%d", sp->sp.code);
				jwt_encoded = stir_shaken_acme_generate_cert_req_payload(ss, sp->sp.kid, sp->sp.nonce, http_req.url, sp->sp.csr.req, sp->sp.nb, sp->sp.na, spc, sp->sp.keys.priv_raw, sp->sp.keys.priv_raw_len, &jwt_decoded);
				if (!jwt_encoded || !jwt_decoded) {
					stir_shaken_set_error(ss, "Failed to generate JWT payload", STIR_SHAKEN_ERROR_JWT);
					free((void *)http_req.url);
					goto fail;
				}

				fprintif(STIR_SHAKEN_LOGLEVEL_BASIC, "\nHTTP POSTing JWT:\n%s\n", jwt_decoded);
				stir_shaken_free_jwt_str(jwt_decoded);
				jwt_decoded = NULL;

				if (STIR_SHAKEN_STATUS_OK != stir_shaken_sp_cert_req(ss, &http_req, jwt_encoded, sp->sp.keys.priv_raw, sp->sp.keys.priv_raw_len, spc, sp->sp.spc_token)) {
					stir_shaken_set_error(ss, "SP certificate request failed", STIR_SHAKEN_ERROR_ACME);
					goto fail;
				}

				fprintif(STIR_SHAKEN_LOGLEVEL_BASIC, "Loading certificate into X509...\n");
				if (STIR_SHAKEN_STATUS_OK != stir_shaken_load_x509_from_mem(ss, &sp->sp.cert.x, NULL, http_req.response.mem.mem)) {
					stir_shaken_set_error(ss, "Failed to load SP certificate into X509", STIR_SHAKEN_ERROR_ACME);
					goto fail;
				}

				fprintif(STIR_SHAKEN_LOGLEVEL_BASIC, "Saving certificate as %s...\n", sp->sp.cert_name);
				if (STIR_SHAKEN_STATUS_OK != stir_shaken_x509_to_disk(ss, sp->sp.cert.x, sp->sp.cert_name)) {
					stir_shaken_set_error(ss, "Failed to save SP certificate", STIR_SHAKEN_ERROR_ACME);
					goto fail;
				}
			}

			break;

		case COMMAND_PA:

			fprintif(STIR_SHAKEN_LOGLEVEL_BASIC, "Starting PA service...\n");
			break;

		case COMMAND_JWT_KEY_CHECK:

			fprintif(STIR_SHAKEN_LOGLEVEL_BASIC, "Loading key...\n");
			options->keys.pub_raw_len = STIR_SHAKEN_PRIV_KEY_RAW_BUF_LEN;
			if (STIR_SHAKEN_STATUS_OK != stir_shaken_load_key_raw(ss, options->public_key_name, options->keys.pub_raw, &options->keys.pub_raw_len)) {
				goto fail;
			}

			fprintif(STIR_SHAKEN_LOGLEVEL_BASIC, "Verifying JWT against the key...\n");
			if (jwt_decode(&jwt, options->jwt, options->keys.pub_raw, options->keys.pub_raw_len)) {
				stir_shaken_set_error(ss, "JWT did not pass verification", STIR_SHAKEN_ERROR_SIP_438_INVALID_IDENTITY_HEADER);
				fprintif(STIR_SHAKEN_LOGLEVEL_BASIC, "JWT and public key don't match\n");
				goto fail;
			}

			fprintif(STIR_SHAKEN_LOGLEVEL_BASIC, "Verified. JWT and public key match\n");

			jwt_free(jwt);
			jwt = NULL;
			break;

		case COMMAND_JWT_CHECK:

			{

				unsigned char cert_raw[STIR_SHAKEN_BUFLEN] = { 0 };
				int cert_raw_len = STIR_SHAKEN_BUFLEN;
				char *passport_decoded = NULL;


				vs = stir_shaken_vs_create(ss);
				if (!vs) {
					fprintif(STIR_SHAKEN_LOGLEVEL_BASIC, "Cannot create Verification Service\n");
					goto fail;
				}

				stir_shaken_vs_set_connect_timeout(ss, vs, options->connect_timeout_s);
				stir_shaken_vs_set_x509_cert_path_check(ss, vs, options->x509_cert_path_check);

				if (options->x509_cert_path_check) {
					status = stir_shaken_vs_load_ca_dir(ss, vs, options->ca_dir_name);
					if (STIR_SHAKEN_STATUS_OK != status) {
						fprintif(STIR_SHAKEN_LOGLEVEL_BASIC, "Failed to init X509 cert store");
						goto fail;
					}
				}

				// For pure Shaken we would have PASSporT
				status = stir_shaken_vs_passport_verify(ss, vs, options->jwt, &cert, &passport);
				if (STIR_SHAKEN_STATUS_OK != status) {
					fprintif(STIR_SHAKEN_LOGLEVEL_BASIC, "PASSporT failed verification\n");
					goto fail;
				}

				passport_decoded = stir_shaken_passport_dump_str(ss, passport, 1);
				if (passport_decoded) {
					printf("\nPASSporT is:\n%s\n", passport_decoded);
					stir_shaken_free_jwt_str(passport_decoded);
					passport_decoded = NULL;
				}


				if (STIR_SHAKEN_STATUS_OK != stir_shaken_get_x509_raw(ss, cert->x, cert_raw, &cert_raw_len)) {
					fprintif(STIR_SHAKEN_LOGLEVEL_BASIC, "Cannot read certificate\n");
					goto fail;
				}

				fprintif(STIR_SHAKEN_LOGLEVEL_BASIC, "\nReferenced certificate is:\n\n%s\n", cert_raw);

				if (STIR_SHAKEN_STATUS_OK != stir_shaken_read_cert_fields(ss, cert)) {
					fprintif(STIR_SHAKEN_LOGLEVEL_BASIC, "Cannot parse referenced certificate\n");
					goto fail;
				}

				fprintif(STIR_SHAKEN_LOGLEVEL_BASIC, "Certificate summary (for details: openssl x509 -in cert.pem -noout -text):\n\n");
				stir_shaken_print_cert_fields(stderr, cert);
				fprintif(STIR_SHAKEN_LOGLEVEL_BASIC, "\nVerified (%s X509 cert path check). JWT matches the referenced certificate by signature check, %s.\n", options->x509_cert_path_check ? "with" : "without", options->x509_cert_path_check ? "certificate is trusted (derived from trusted CA roots)" : "certificate may not be trusted (because it hasn't been checked with X509 cert path check)");

				stir_shaken_cert_destroy(&cert);
				stir_shaken_vs_destroy(&vs);
			}

			break;

		case COMMAND_JWT_DUMP:

			if (0 != jwt_decode(&jwt, options->jwt, NULL, 0)) {
				stir_shaken_set_error(ss, "Token is not JWT", STIR_SHAKEN_ERROR_JWT);
				goto fail;
			}

			jwt_decoded = jwt_dump_str(jwt, 1);
			if (!jwt_decoded) {
				stir_shaken_set_error(ss, "Cannot print JWT", STIR_SHAKEN_ERROR_JWT);
				goto fail;
			}

			fprintif(STIR_SHAKEN_LOGLEVEL_BASIC, "JWT is:\n\n%s\n", jwt_decoded);

			stir_shaken_free_jwt_str(jwt_decoded);
			jwt_decoded = NULL;

			break;

		case COMMAND_PASSPORT_CREATE:

			{
				fprintif(STIR_SHAKEN_LOGLEVEL_BASIC, "Loading key...\n");
				options->keys.priv_raw_len = STIR_SHAKEN_PRIV_KEY_RAW_BUF_LEN;
				if (STIR_SHAKEN_STATUS_OK != stir_shaken_load_key_raw(ss, options->private_key_name, options->keys.priv_raw, &options->keys.priv_raw_len)) {
					goto fail;
				}

				fprintif(STIR_SHAKEN_LOGLEVEL_BASIC, "Assigning parameters to PASSporT...\n");
				passport = stir_shaken_passport_create(ss, &sp->sp.passport_params, options->keys.priv_raw, options->keys.priv_raw_len);
				if (!passport) {
					goto fail;
				}

				fprintif(STIR_SHAKEN_LOGLEVEL_BASIC, "Getting plain version of PASSporT (decoded, not signed, with no signature)...\n");
				p1 = stir_shaken_passport_dump_str(ss, passport, 1);
				if (stir_shaken_zstr(p1)) {
					goto fail;
				}

				fprintif(STIR_SHAKEN_LOGLEVEL_BASIC, "PASSporT is:\n%s\n", p1);

				fprintif(STIR_SHAKEN_LOGLEVEL_BASIC, "Encoding (signing) using submitted key...\n");
				status = stir_shaken_passport_sign(ss, passport, NULL, 0, &p2);
				if (STIR_SHAKEN_STATUS_OK != status) {
					goto fail;
				}

				fprintif(STIR_SHAKEN_LOGLEVEL_BASIC, "PASSporT encoded (signed) is:\n%s\n", p2);

				fprintif(STIR_SHAKEN_LOGLEVEL_BASIC, "Getting PASSporT wrapped into SIP Identity Header...\n");
				options->keys.priv_raw_len = sizeof(options->keys.priv_raw);
				sih = stir_shaken_jwt_sip_identity_create(ss, passport, options->keys.priv_raw, options->keys.priv_raw_len);
				if (!sih) {
					goto fail;
				}
				fprintif(STIR_SHAKEN_LOGLEVEL_BASIC, "\nSIP Identity Header is:\n%s\n\n", sih);

				if (STIR_SHAKEN_STATUS_OK != stir_shaken_save_to_file(ss, "PASSporT is:\n", options->file)) {
					goto fail;
				}

				if (STIR_SHAKEN_STATUS_OK != stir_shaken_append_to_file(ss, p1, options->file)) {
					goto fail;
				}

				if (STIR_SHAKEN_STATUS_OK != stir_shaken_append_to_file(ss, "\nPASSporT signed is:\n", options->file)) {
					goto fail;
				}

				if (STIR_SHAKEN_STATUS_OK != stir_shaken_append_to_file(ss, p2, options->file)) {
					goto fail;
				}

				if (STIR_SHAKEN_STATUS_OK != stir_shaken_append_to_file(ss, "\n\nSIP Identity Header with PASSporT is:\n", options->file)) {
					goto fail;
				}

				if (STIR_SHAKEN_STATUS_OK != stir_shaken_append_to_file(ss, sih, options->file)) {
					goto fail;
				}

				if (STIR_SHAKEN_STATUS_OK != stir_shaken_append_to_file(ss, "\n", options->file)) {
					goto fail;
				}

				stir_shaken_free_jwt_str(p1);
				p1 = NULL;

				stir_shaken_free_jwt_str(p2);
				p2 = NULL;

				free(sih);
				sih = NULL;

				stir_shaken_passport_destroy(&passport);
			}
			break;

		case COMMAND_VERSION:

			fprintif(STIR_SHAKEN_LOGLEVEL_BASIC, "libstirshaken git version is: %s\n", stir_shaken_get_git_version());
			break;

		case COMMAND_UNKNOWN:
		default:
			goto fail;
	}

	if (spc_token_encoded) {
		stir_shaken_free_jwt_str(spc_token_encoded);
		spc_token_encoded = NULL;
	}
	if (spc_token_decoded) {
		stir_shaken_free_jwt_str(spc_token_decoded);
		spc_token_decoded = NULL;
	}
	if (jwt) {
		jwt_free(jwt);
		jwt = NULL;
	}
	stir_shaken_passport_params_destroy(&sp->sp.passport_params);
	stir_shaken_deinit();

	return STIR_SHAKEN_STATUS_OK;

fail:

	if (spc_token_encoded) {
		stir_shaken_free_jwt_str(spc_token_encoded);
		spc_token_encoded = NULL;
	}
	if (spc_token_decoded) {
		stir_shaken_free_jwt_str(spc_token_decoded);
		spc_token_decoded = NULL;
	}
	if (jwt) {
		jwt_free(jwt);
		jwt = NULL;
	}
	if (p1) {
		stir_shaken_free_jwt_str(p1);
		p1 = NULL;
	}
	if (p2) {
		stir_shaken_free_jwt_str(p2);
		p2 = NULL;
	}
	if (sih) {
		free(sih);
		sih = NULL;
	}
	stir_shaken_passport_destroy(&passport);
	stir_shaken_passport_params_destroy(&sp->sp.passport_params);
	stir_shaken_cert_destroy(&cert);
	stir_shaken_vs_destroy(&vs);
	stir_shaken_deinit();

	return STIR_SHAKEN_STATUS_FALSE;
}
