#include "server.h"

t_log* logger;

int main(void) {
    logger = log_create("tp0.log", "Servidor", 1, LOG_LEVEL_INFO);

    int servidor_fd = iniciar_servidor();
    log_info(logger, "Servidor listo para recibir al cliente");
    
    int cliente_fd = esperar_cliente(servidor_fd);

    t_list* lista;
    while (1) {
        int cod_op = recibir_operacion(cliente_fd);
        switch (cod_op) {
        case MENSAJE:
            recibir_mensaje(cliente_fd);
            break;
        case PAQUETE:
            lista = recibir_paquete(cliente_fd);
            list_iterate(lista, (void*) log_info);
            break;
        case -1:
            log_error(logger, "El cliente se desconectó. Terminando servidor");
            return EXIT_FAILURE;
        default:
            log_warning(logger, "Operación desconocida.");
            break;
        }
    }
    return EXIT_SUCCESS;
}