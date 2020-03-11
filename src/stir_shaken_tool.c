#include <stir_shaken_tool.h>


static void stirshaken_usage(const char *name)
{
	if (name == NULL)
		return;
	
	fprintf(stderr, "\nusage:\t command\n\n", name);
	fprintf(stderr, "\t\t %s --%s pub.pem --%s priv.pem\n", COMMAND_NAME_KEYS, OPTION_NAME_PUBKEY, OPTION_NAME_PRIVKEY);
	fprintf(stderr, "\t\t %s --%s key --%s key --%s C --%s CN --%s CODE -f csrName\n", COMMAND_NAME_CSR, OPTION_NAME_PRIVKEY, OPTION_NAME_PUBKEY, OPTION_NAME_SUBJECT_C, OPTION_NAME_SUBJECT_CN, OPTION_NAME_SPC);
	fprintf(stderr, "\t\t %s --%s %s --%s key --%s key --%s C --%s CN --%s SERIAL --%s EXPIRY -f certName\n", COMMAND_NAME_CERT, OPTION_NAME_TYPE, OPTION_NAME_TYPE_CA, OPTION_NAME_PRIVKEY, OPTION_NAME_PUBKEY, OPTION_NAME_ISSUER_C, OPTION_NAME_ISSUER_CN, OPTION_NAME_SERIAL, OPTION_NAME_EXPIRY);
	fprintf(stderr, "\t\t %s --%s %s --%s key --%s key --%s C --%s CN --%s SERIAL --%s EXPIRY --%s ca.pem --%s csr.pem --%s TNAuthList(URI) -f certName\n", COMMAND_NAME_CERT, OPTION_NAME_TYPE, OPTION_NAME_TYPE_SP, OPTION_NAME_PRIVKEY, OPTION_NAME_PUBKEY, OPTION_NAME_ISSUER_C, OPTION_NAME_ISSUER_CN, OPTION_NAME_SERIAL, OPTION_NAME_EXPIRY, OPTION_NAME_CA_CERT, OPTION_NAME_CSR, OPTION_NAME_TN_AUTH_LIST_URI);
	fprintf(stderr, "\t\t %s -f certName\n", COMMAND_NAME_INSTALL_CERT);
	fprintf(stderr, "\t\t %s --%s 80\n", COMMAND_NAME_CA, OPTION_NAME_PORT);
	fprintf(stderr, "\t\t %s --%s 80\n", COMMAND_NAME_PA, OPTION_NAME_PORT);
	fprintf(stderr, "\t\t %s --%s URL\n", COMMAND_NAME_SP_SPC_REQ, OPTION_NAME_URL);
	fprintf(stderr, "\t\t %s --%s URL\n", COMMAND_NAME_SP_CERT_REQ, OPTION_NAME_URL);
	fprintf(stderr, "\n");
	fprintf(stderr, "\t\t Each command accepts logging verbosity option:\n");
	fprintf(stderr, "\t\t --v\t\tbasic logging\n");
	fprintf(stderr, "\t\t --vv\t\tmedium logging\n");
	fprintf(stderr, "\t\t --vvv\t\thigh logging\n");
	fprintf(stderr, "\n");
	fprintf(stderr, "\t\t %s			: generate key pair\n", COMMAND_NAME_KEYS);
	fprintf(stderr, "\t\t %s			: generate X509 certificate request for SP identified by SP Code given to --spc\n", COMMAND_NAME_CSR);
	fprintf(stderr, "\t\t %s			: generate X509 certificate (end entity for --type %s and self-signed for --type %s)\n", COMMAND_NAME_CERT, OPTION_NAME_TYPE_SP, OPTION_NAME_TYPE_CA);
	fprintf(stderr, "\t\t %s		: hash CA certificate and copy into CA dir\n", COMMAND_NAME_INSTALL_CERT);
	fprintf(stderr, "\t\t %s			: run CA service on port given to --%s\n", COMMAND_NAME_CA, OPTION_NAME_PORT);
	fprintf(stderr, "\t\t %s			: run PA service on port given to --%s\n", COMMAND_NAME_PA, OPTION_NAME_PORT);
	fprintf(stderr, "\t\t %s		: request SP Code token from PA at url given to --%s\n", COMMAND_NAME_SP_SPC_REQ, OPTION_NAME_URL);
	fprintf(stderr, "\t\t %s		: request SP certificate for Service Provider identified by number given to --%s from CA at url given to --%s\n\n", COMMAND_NAME_SP_CERT_REQ, OPTION_NAME_SPC, OPTION_NAME_URL);
	fprintf(stderr, "\n");
}

void stirshaken_range_error(char arg, unsigned long val)
{
	fprintf(stderr, "\nERR, argument [%c] too big [%lu]\n\n", arg, val);
}

static void help_hint(const char *name)
{
	if (name == NULL)
		return;
	fprintf(stderr, "\nTry %s --help for more information.\n", name);
	return;
}


int main(int argc, char *argv[])
{
	int c = -1;
	char *pCh = NULL;
	unsigned long long  helper;
	stir_shaken_status_t status = STIR_SHAKEN_STATUS_OK;
	stir_shaken_context_t ss = { 0 };
	const char *error_description = NULL;
	stir_shaken_error_t error_code = STIR_SHAKEN_ERROR_GENERAL;
	int command = COMMAND_UNKNOWN;
	const char *command_name = COMMAND_NAME_UNKNOWN;
	int option_index = 0;
	struct option long_options[] = {
		{ OPTION_NAME_PUBKEY, required_argument, 0, OPTION_PUBKEY },
		{ OPTION_NAME_PRIVKEY, required_argument, 0, OPTION_PRIVKEY },
		{ OPTION_NAME_ISSUER_C, required_argument, 0, OPTION_ISSUER_C },
		{ OPTION_NAME_ISSUER_CN, required_argument, 0, OPTION_ISSUER_CN },
		{ OPTION_NAME_SERIAL, required_argument, 0, OPTION_SERIAL },
		{ OPTION_NAME_EXPIRY, required_argument, 0, OPTION_EXPIRY },
		{ OPTION_NAME_TYPE, required_argument, 0, OPTION_TYPE },
		{ OPTION_NAME_HELP, no_argument, 0, OPTION_HELP },
		{ OPTION_NAME_SUBJECT_C, required_argument, 0, OPTION_SUBJECT_C },
		{ OPTION_NAME_SUBJECT_CN, required_argument, 0, OPTION_SUBJECT_CN },
		{ OPTION_NAME_SPC, required_argument, 0, OPTION_SPC },
		{ OPTION_NAME_SPC_TOKEN, required_argument, 0, OPTION_SPC_TOKEN },
		{ OPTION_NAME_CA_CERT, required_argument, 0, OPTION_CA_CERT },
		{ OPTION_NAME_CSR, required_argument, 0, OPTION_CSR },
		{ OPTION_NAME_TN_AUTH_LIST_URI, required_argument, 0, OPTION_TN_AUTH_LIST_URI },
		{ OPTION_NAME_PORT, required_argument, 0, OPTION_PORT },
		{ OPTION_NAME_URL, required_argument, 0, OPTION_URL },
		{ OPTION_NAME_V, no_argument, 0, OPTION_V },
		{ OPTION_NAME_VV, no_argument, 0, OPTION_VV },
		{ OPTION_NAME_VVV, no_argument, 0, OPTION_VVV },
		{ 0 }
	};


	if (argc < 2) {
		stirshaken_usage(argv[0]);
		exit(EXIT_FAILURE);
	}

	// Parse options

	while ((c = getopt_long(argc, argv, "f:", long_options, &option_index)) != -1) {

		if (c < OPTION_MAX) {
			fprintf(stderr, "\n+ Processing OPTION %d (%s)\n", c, long_options[option_index].name);
		} else {
			fprintf(stderr, "\n+ Processing OPTION %d ('%c')\n", c, c);
		}

		switch (c) {

			case OPTION_PUBKEY:
				STIR_SHAKEN_CHECK_OPTARG
				strncpy(options.public_key_name, optarg, STIR_SHAKEN_BUFLEN);
				fprintf(stderr, "Public key name is: %s\n", options.public_key_name);
				break;

			case OPTION_PRIVKEY:
				STIR_SHAKEN_CHECK_OPTARG
				strncpy(options.private_key_name, optarg, STIR_SHAKEN_BUFLEN);
				fprintf(stderr, "Private key name is: %s\n", options.private_key_name);
				break;

			case OPTION_ISSUER_C:
				STIR_SHAKEN_CHECK_OPTARG
				strncpy(options.issuer_c, optarg, STIR_SHAKEN_BUFLEN);
				fprintf(stderr, "Issuer C is: %s\n", options.issuer_c);
				break;
			
			case OPTION_ISSUER_CN:
				STIR_SHAKEN_CHECK_OPTARG
				strncpy(options.issuer_cn, optarg, STIR_SHAKEN_BUFLEN);
				fprintf(stderr, "Issuer CN is: %s\n", options.issuer_cn);
				break;
			
			case OPTION_SERIAL:
				helper = strtoul(optarg, &pCh, 10);
				STIR_SHAKEN_CHECK_CONVERSION
				options.serial = helper;
				break;
			
			case OPTION_EXPIRY:
				helper = strtoul(optarg, &pCh, 10);
				STIR_SHAKEN_CHECK_CONVERSION
				options.expiry_days = helper;
				break;

			case OPTION_TYPE:
				if (!strcmp(optarg, OPTION_NAME_TYPE_CA)) {
					
					options.command_cert_type = COMMAND_CERT_CA;
					fprintf(stderr, "Certificate type is: CA\n");
				
				} else if (!strcmp(optarg, OPTION_NAME_TYPE_SP)) {

					options.command_cert_type = COMMAND_CERT_SP;
					fprintf(stderr, "Certificate type is: SP\n");

				} else {
					fprintf(stderr, "Invalid option %s for --type\n", optarg);
					goto fail;
				}

				break;

			case OPTION_HELP:
				stirshaken_usage(argv[0]);
				exit(EXIT_SUCCESS);
				break;

			case 'f':
				STIR_SHAKEN_CHECK_OPTARG
				strncpy(options.file, optarg, STIR_SHAKEN_BUFLEN);
				fprintf(stderr, "Output file is: %s\n", options.file);
				break;

			case OPTION_SUBJECT_C:
				STIR_SHAKEN_CHECK_OPTARG
				strncpy(options.subject_c, optarg, STIR_SHAKEN_BUFLEN);
				fprintf(stderr, "Subject C is: %s\n", options.subject_c);
				break;
			
			case OPTION_SUBJECT_CN:
				STIR_SHAKEN_CHECK_OPTARG
				strncpy(options.subject_cn, optarg, STIR_SHAKEN_BUFLEN);
				fprintf(stderr, "Subject CN is: %s\n", options.subject_cn);
				break;
			
			case OPTION_SPC:
				STIR_SHAKEN_CHECK_OPTARG
				strncpy(options.spc, optarg, STIR_SHAKEN_BUFLEN);
				fprintf(stderr, "SPC is: %s\n", options.spc);
				break;
			
			case OPTION_SPC_TOKEN:
				STIR_SHAKEN_CHECK_OPTARG
				strncpy(options.spc_token, optarg, STIR_SHAKEN_BUFLEN);
				fprintf(stderr, "SPC token is: %s\n", options.spc_token);
				break;
			
			case OPTION_CA_CERT:
				STIR_SHAKEN_CHECK_OPTARG
				strncpy(options.ca_cert, optarg, STIR_SHAKEN_BUFLEN);
				fprintf(stderr, "CA certificate is: %s\n", options.ca_cert);
				break;
			
			case OPTION_CSR:
				STIR_SHAKEN_CHECK_OPTARG
				strncpy(options.csr_name, optarg, STIR_SHAKEN_BUFLEN);
				fprintf(stderr, "CSR is: %s\n", options.csr_name);
				break;
			
			case OPTION_TN_AUTH_LIST_URI:
				STIR_SHAKEN_CHECK_OPTARG
				strncpy(options.tn_auth_list_uri, optarg, STIR_SHAKEN_BUFLEN);
				fprintf(stderr, "TNAuthList URI is: %s\n", options.tn_auth_list_uri);
				break;

			case OPTION_PORT:
				helper = strtoul(optarg, &pCh, 10);
				STIR_SHAKEN_CHECK_CONVERSION
				options.port = helper;
				fprintf(stderr, "Port is: %u\n", options.port);
				break;

			case OPTION_URL:
				STIR_SHAKEN_CHECK_OPTARG
				strncpy(options.url, optarg, STIR_SHAKEN_BUFLEN);
				fprintf(stderr, "URL is: %s\n", options.url);
				break;

			case OPTION_V:
				options.loglevel = STIR_SHAKEN_LOGLEVEL_BASIC;
				break;
			
			case OPTION_VV:
				options.loglevel = STIR_SHAKEN_LOGLEVEL_MEDIUM;
				break;

			case OPTION_VVV:
				options.loglevel = STIR_SHAKEN_LOGLEVEL_HIGH;
				break;

			case '?':
				if (optopt == 'f') {
					fprintf(stderr, "\nOption -%c requires an argument.\n", optopt);
				} else if (isprint(optopt))
					fprintf(stderr,"Unknown option '-%c'.\n", optopt);
				else {
					fprintf(stderr, "Are there any long options? Please check that you have typed them correctly.\n");
				}
				stirshaken_usage(argv[0]);
				exit(EXIT_FAILURE);

			default:
				fprintf(stderr, "Error. Missing options?");
				help_hint(argv[0]);
				exit(EXIT_FAILURE);
		}
	}

	if (1 != (argc - optind)) {
		fprintf(stderr, "\nInvalid number of non-option arguments.\nThere should be 1 non-option argument\n");
		help_hint(argv[0]);
		exit(EXIT_FAILURE);
	}
	
	// Parse the comamnd

	fprintf(stderr, "\n=== PARSING COMMAND\n\n");
	command = stirshaken_command_configure(&ss, argv[optind], &ca, &pa, &sp, &options);
	if (COMMAND_UNKNOWN == command) {
		fprintf(stderr, "\nError. Invalid command. Type %s --help for usage instructions\n", argv[0]);
		PRINT_SHAKEN_ERROR_IF_SET
		goto fail;
	}


	// Validate the command
	
	fprintf(stderr, "\n=== VALIDATING COMMAND\n\n");
	if (STIR_SHAKEN_STATUS_OK != stirshaken_command_validate(&ss, command, &ca, &pa, &sp, &options)) {
		fprintf(stderr, "\nError. Invalid parameters. Type %s --help for usage instructions\n", argv[0]);
		PRINT_SHAKEN_ERROR_IF_SET
		goto fail;
	}

	// Process the command
	
	fprintf(stderr, "\n=== PROCESSING COMMAND\n\n");
	if (STIR_SHAKEN_STATUS_OK != stirshaken_command_execute(&ss, command, &ca, &pa, &sp, &options)) {
		fprintf(stderr, "\nError. Command failed.\n");
		PRINT_SHAKEN_ERROR_IF_SET
		goto fail;
	}
	
	fprintf(stderr, "\n=== Done. Thank you.\n\n");
	return EXIT_SUCCESS;

fail:
	fprintf(stderr, "Error\n");
	return EXIT_FAILURE;
}
