#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<openssl/bio.h>
#include<openssl/ssl.h>
#include<openssl/err.h>


BIO		*create_ssl_server(int port, char *server_pem, char *p_key)
{
  BIO		*sbio, *bbio, *acpt;
  SSL_CTX	*ctx;
  SSL		*ssl;
  char		portstr[10];

  ERR_load_crypto_strings ();
  ERR_load_SSL_strings();
  SSL_library_init();

  ctx = SSL_CTX_new(SSLv23_server_method());

  if (!SSL_CTX_use_certificate_file(ctx, server_pem, SSL_FILETYPE_PEM)
      || !SSL_CTX_use_PrivateKey_file(ctx, p_key, SSL_FILETYPE_PEM)
      || !SSL_CTX_check_private_key(ctx))
    {
      fprintf(stderr, "Erreur d'initialisation SSL_CTX\n");
      ERR_print_errors_fp(stderr);
      return(NULL);
    }

  sbio = BIO_new_ssl(ctx, 0);
  BIO_get_ssl(sbio, &ssl);

  if (!ssl)
    {
      fprintf(stderr, "Pointeur '*ssl' introuvable\n");
      BIO_free_all(sbio);
      return(NULL);
    }

  SSL_set_mode(ssl, SSL_MODE_AUTO_RETRY);
  bbio = BIO_new(BIO_f_buffer());
  sbio = BIO_push(bbio, sbio);
  snprintf(portstr, 10, "%d", port);
  acpt = BIO_new_accept(portstr);
  BIO_set_accept_bios(acpt, sbio);

  if (BIO_do_accept(acpt) <= 0)
    {
      fprintf(stderr, "Mise en place di BIO impossible pour accept()\n");
      ERR_print_errors_fp(stderr);
      BIO_free_all(sbio);
      return(NULL);
    }

  if (BIO_do_accept(acpt) <= 0)
    {
      fprintf(stderr, "Erreur de connexion\n");
      ERR_print_errors_fp(stderr);
      BIO_free_all(acpt);
      BIO_free_all(sbio);
      return(NULL);
    }

  sbio = BIO_pop(acpt);
  BIO_free_all(acpt);

  if (BIO_do_handshake(sbio) <= 0)
    {
      fprintf(stderr, "Erreur de negociation SSL\n");
      ERR_print_errors_fp(stderr);
      return(0);
    }
  return(sbio);
}


void	trade(BIO *sbio)
{
  char	str[1024];
  int	len;
  int	i;

  len = 0;
  BIO_puts(sbio, "Bonjour, Identifiez vous\n");
  BIO_flush(sbio);


  while(len <= 0)
    {
      len = BIO_gets(sbio, str, sizeof(str));
    }

  for (i = len - 1; i >= 0; i--)
    {
      if ((str[i] != '\n') && (str[i] != '\r'))
	break;
      str[i] = '\0';
    }

  BIO_puts(sbio, "Bienvenue, ");
  BIO_puts(sbio, str);
  BIO_puts(sbio, ".\n");
  BIO_flush(sbio);
  BIO_free_all(sbio);
}


int		main()
{
  BIO		*sbio;

  sbio = create_ssl_server(2000, "server.pem", "privkey.pem");
  if (NULL == sbio)
    {
      fprintf(stderr, "Erreur de creation du serveur SSL\n");
      exit(EXIT_FAILURE);
    }
  trade(sbio);
  exit(EXIT_SUCCESS);
}
