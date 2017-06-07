#ifdef __cplusplus
extern "C" {
#endif

#include <string.h>
#include "sqlite3.h"


static sqlite3 *db;

extern struct node* activities;//estrutura que guarda as atividades preferidas
extern struct date_node* date_node;

char *create_trail(void);
char *database_close_trail(void);
char *insert_data(char *local, char *activity);
char *insert_data_d(char *local, char *activity, char *data);
char *preferred_activity();
char *preferred_activity_local(char *local);
//consultar dados da pilha de favoritos
int size_preferred_list();
char *get_activity_pos(int pos);

//em desuso
char *consult_period_date(char *data1, char *data2);
int queue_date_size();
char *return_local_date(int position);
char *return_activity_date(int position);
char *return_date_date(int position);

//filtrar atividade por data
int find_activity(char *local, char *date);
char *return_activity(int position);
//deletar dados do local e deletar banco de dados
char *delete_local(char *local);
char *drop();
//consulta de todos os dados
int return_number_records();
char *return_consult_local(int position);
char *return_consult_activity(int position);
char *return_consult_data(int position);

//consultada da data
int consult_period_date2(char *date1, char *date2);
char *return_period_date_local(int position);
char *return_period_date_activity(int position);
char *return_period_date_date(int position);


//int main(void);
char* getHead(struct node *node);

#ifdef __cplusplus
}
#endif
