#include <stdio.h>
#include "sqlite3.h"
#include <pthread.h>
#include <dlfcn.h>
#include "database.h"

#include<string.h>
#include<stdlib.h>

struct node* activities = NULL;
struct date_node* date_node = NULL;

char *create_trail(void){
   int result;
   result = sqlite3_open("/home/lucksim/Downloads/data/banco.db", &db);
   
   char *resposta = NULL;

   if (result!=SQLITE_OK) {
       int tamanho_err_msg = strlen(sqlite3_errmsg(db));
       resposta = (char *)malloc(strlen("create_trail - Error -")+tamanho_err_msg+1);
     
       sprintf(resposta, "create_trail - Error - %s ", sqlite3_errmsg(db));
       sqlite3_close(db);
       return resposta;
   } 

   char *erro=NULL;
   int result2 = sqlite3_exec(db, "CREATE TABLE TRAIL (LOCAL VARCHAR(50), ACTIVITY VARCHAR(50), DATA DATE)", NULL, NULL, erro);
   if (!erro){
   	int tam_msg = strlen("create_trail - Ok");
        resposta = (char *)malloc(tam_msg+1);
        strcpy(resposta, "create_trail - Ok");
    }else{
	int tam_msg = strlen("create_trail - Warning - Table already created");
	resposta = (char *)malloc(tam_msg+1);
	strcpy(resposta, "create_trail - Warning - Table already created");
   }

return resposta;
}

char *insert_data_d(char *local, char *activity, char *data) {
   char *sql=NULL;
   char *error=NULL;
   char *resposta = NULL;

   int tamanho_stmt = strlen("INSERT INTO TRAIL (LOCAL, ACTIVITY, DATA) VALUES ('', '', '')");	
   int tamanho_char = strlen(local);
   int tamanho_char2 = strlen(activity);
   int tamanho_char3 = strlen(data);
   
   sql = (char *)malloc(tamanho_stmt+tamanho_char+tamanho_char2+tamanho_char3+1);
 
   sprintf(sql, "INSERT INTO TRAIL (LOCAL, ACTIVITY, DATA) VALUES ('%s', '%s', '%s')", local, activity, data);
   
   //sprintf(sql, "INSERT INTO TRAIL (LOCAL, ACTIVITY, DATA) VALUES ('%s', '%s', DATETIME('NOW'))", local, activity);
   
   sqlite3_exec(db, sql, NULL, NULL, &error);
   
   if (!error){
	int tam_msg = strlen("insert data - Ok");
	resposta = (char *)malloc(tam_msg+1);
	strcpy(resposta, "insert data - Ok");	
   }else{
	int tam_msg = strlen("insert data - Error");
	//int tam_msg_error = strlen(error);
	resposta = (char *)malloc(tam_msg+1);
	strcpy(resposta, "insert data - Error");
	return resposta;
   }
return resposta;	  
}

char *insert_data(char *local, char *activity) {
   char *sql;
   char *error=NULL;
   char *resposta = NULL;

   int tamanho_stmt = strlen("INSERT INTO TRAIL (LOCAL, ACTIVITY, DATA) VALUES ('', '', 'DATETIME('NOW', 'LOCALTIME')')");
   int tamanho_char = strlen(local);
   int tamanho_char2 = strlen(activity);
   //int tamanho_char3 = strlen(data);
   
   sql = (char *)malloc(tamanho_stmt+tamanho_char+tamanho_char2+1);
 
   //sprintf(sql, "INSERT INTO TRAIL (LOCAL, ACTIVITY, DATA) VALUES ('%s', '%s', '%s')", local, activity, data);
   
   sprintf(sql, "INSERT INTO TRAIL (LOCAL, ACTIVITY, DATA) VALUES ('%s', '%s', DATETIME('NOW', 'LOCALTIME'))", local, activity);
   
   sqlite3_exec(db, sql, NULL, NULL, &error);
   
   if (!error){
	int tam_msg = strlen("insert data - Ok");
	resposta = (char *)malloc(tam_msg+1);
	strcpy(resposta, "insert data - Ok");	
   }else{
	int tam_msg = strlen("insert data - Error - ");
	int tam_msg_error = strlen(error);
	resposta = (char *)malloc(tam_msg+tam_msg_error+1);
	sprintf(resposta, "insert data - Error - %s", error);
	return resposta;
   }
return resposta;	  
}

char *database_close_trail(void) {
    int result = sqlite3_close(db);
    char *resp = NULL;

    if (result == SQLITE_BUSY){
        resp = (char *)malloc(strlen("database_close_trail - Ok"));    
	strcpy(resp, "database_close_trail - Ok");
    }else {
        resp = (char *)malloc(strlen("database_close_trail - Error"));    
	strcpy(resp, "database_close_trail - Error");
    }	
    
    return resp;
}

//////////////*Estruturas de filas encadeadas e mergesort*//////////////////////////

//
  
struct node
{
    int count;
    char *activity;
    struct node* next;
};

struct date_node{
    char *local;
    char *activity;
    char *date;
    struct date_node* next;
};

/* function prototypes */
struct node* SortedMerge(struct node* a, struct node* b);
void FrontBackSplit(struct node* source, struct node** frontRef, struct node** backRef); 

void MergeSort(){
  MergeSort2(&activities); 
 
}

void MergeSort2(struct node** headRef)
{
  struct node* head = *headRef;
  struct node* a;
  struct node* b;
 
  /* Base case -- length 0 or 1 */
  if ((head == NULL) || (head->next == NULL))
  {
    return;
  }
 
  /* Split head into 'a' and 'b' sublists */
  FrontBackSplit(head, &a, &b);
 
  /* Recursively sort the sublists */
  MergeSort2(&a);
  MergeSort2(&b);
 
  /* answer = merge the two sorted lists together */
  *headRef = SortedMerge(a, b);
}
 
struct node* SortedMerge(struct node* a, struct node* b)
{
  struct node* result = NULL;
 
  /* Base cases */
  if (a == NULL)
     return(b);
  else if (b==NULL)
     return(a);
 
  /* Pick either a or b, and recur */
  /* >= indica que está em ordem ascendente */
  if (a->count >= b->count)
  {
     result = a;
     result->next = SortedMerge(a->next, b);
  }
  else
  {
     result = b;
     result->next = SortedMerge(a, b->next);
  }
  return(result);
}
 
void FrontBackSplit(struct node* source, struct node** frontRef, struct node** backRef)
{
  struct node* fast;
  struct node* slow;
  if (source==NULL || source->next==NULL)
  {
    /* length < 2 cases */
    *frontRef = source;
    *backRef = NULL;
  }
  else
  {
    slow = source;
    fast = source->next;
 
    /* Advance 'fast' two nodes, and advance 'slow' one node */
    while (fast != NULL)
    {
      fast = fast->next;
      if (fast != NULL)
      {
        slow = slow->next;
        fast = fast->next;
      }
    }
 
    /* 'slow' is before the midpoint in the list, so split it in two
      at that point. */
    *frontRef = source;
    *backRef = slow->next;
    slow->next = NULL;
  }
}
 
void printList(struct node *node)
{
  while(node!=NULL)
  {
   printf("%d, %s \n", node->count, node->activity);
   node = node->next;
  }
}

void printHead(struct node *node)
{
  if(node!=NULL)
  {
   printf("%d, %s \n", node->count, node->activity);
  }
}

char* getHead(struct node *node)
{
  if(node!=NULL)
  {
    return node->activity;//se nodo diferente de NULL, retornar a atividade preferida do usuário;
  }
}


void pushEqual(char *new_activity){
     pushEqual2(activities, new_activity);

}

void pushEqual2(struct node* node, char *new_activity){
        int flag_trocou = 0;      
	while(node!=NULL){
		  if (strcmp(node->activity, new_activity)==0){
			node->count = node->count + 1; // se já contém o nome na lista, aumentar o contador.
			flag_trocou = 1;
                        break;
		}
		node = node->next;
	}
	
	if (flag_trocou==0){
	   push2(&activities, new_activity);	
	}
}


void push2(struct node** head_ref, char *new_activity)
{
  struct node* new_node = (struct node*) malloc(sizeof(struct node));
  new_node->count = 1;
  new_node->activity  = (char *) malloc(tamanho_char(new_activity)+1);
  strcpy(new_node->activity, new_activity);
  new_node->next = (*head_ref);   
  (*head_ref)    = new_node;
}

int get_int_len(int value){
  int l=!value;
  while(value){ l++; value/=10; }
  return l;
}

int tamanho_char(char *string){
  int len1 = strlen(string);
  return len1;	     	
}



//funcao que retorna a atividade preferida do usuário
char *preferred_activity(){

 sqlite3_stmt *res;
 int error = 0;
 int rec_count = 0;
 const char *errMSG;
 const char *tail;
 char* resultado = NULL;

  if(activities != NULL){
 	free(activities);
 	activities = NULL; 
 }

 error = sqlite3_prepare_v2(db, "select * from trail", 1000, &res, &tail);
 
 if (error != SQLITE_OK) {
     resultado = (char *)malloc(strlen("Error - No data")+1);
     strcpy(resultado, "Error - No data");
     return resultado;
 }

 while (sqlite3_step(res) == SQLITE_ROW) {
         
         pushEqual(sqlite3_column_text(res, 1));//coluna atividade
 }

 if(activities!=NULL){	
 	MergeSort();
 	resultado = (char *)malloc(strlen(getHead(activities))+1);
 	strcpy(resultado, getHead(activities));
	return resultado;
 }	

  resultado = (char *)malloc(strlen("Error - No data")+1);
  strcpy(resultado, "Error - No data");
  return resultado;

}

char *preferred_activity_local(char *local){

 sqlite3_stmt *res;
 int error = 0;
 int rec_count = 0;
 const char *errMSG;
 const char *tail;
 char *resultado = NULL;

 if(activities != NULL){
 	free(activities);
 	activities = NULL; 
 }

 int local_lenght = strlen(local);
 
 char *sql = (char *)malloc(sizeof(char *) * 19+local_lenght+1);

 sprintf(sql, "select * from trail where local='%s'", local);

 error = sqlite3_prepare_v2(db, sql, 1000, &res, &tail);

 if (error != SQLITE_OK) {
     resultado = (char *)malloc(strlen("Error - No data")+1);
     strcpy(resultado, "Error - No data");
     return resultado;
 }

 while (sqlite3_step(res) == SQLITE_ROW) {
          pushEqual(sqlite3_column_text(res, 1));//coluna atividade
 }

 if(activities!=NULL){	
 	MergeSort();
 	resultado = (char *)malloc(strlen(getHead(activities))+1);
 	strcpy(resultado, getHead(activities));
	return resultado;
 }	

  resultado = (char *)malloc(strlen("Error - No data")+1);
  strcpy(resultado, "Error - No data");
  return resultado;
}

char *delete_local(char *local){
   char *sql;
   char *erro=NULL;
   char *resposta = NULL;
   int tamanho_local = strlen(local);
   sql = (char *)malloc(sizeof(char) * 34+tamanho_local+1);   
   sprintf(sql, "DELETE FROM TRAIL WHERE LOCAL='%s'", local);
   int result2 = sqlite3_exec(db, sql, NULL, NULL, &erro);
   if (result2){
	 int tamanho_erro = strlen(erro);
	 resposta = (char *)malloc(52+tamanho_erro+1);
	 sprintf(resposta, "Não foi possível realizar a exclusao do registro'%s'", erro);
   } else { 
	resposta = (char *)malloc(32);
        strcpy(resposta, "Operação realizada com sucesso"); 
   } 
 return resposta;
}


char *drop(){
 char *resultado = NULL;

 if (remove("/home/lucksim/Downloads/data/banco.db") == -1){
   resultado = (char *)malloc(strlen("DROP_FAIL")+1);
   strcpy(resultado, "DROP_FAIL");
 } else {
   resultado = (char *)malloc(strlen("DROP_OK")+1);
   if (activities!=NULL) {free(activities); activities=NULL;}
   if (date_node!=NULL) {free(date_node); date_node=NULL;}	
   strcpy(resultado, "DROP_OK");
 }	

 return resultado;
}

void push_date(struct date_node** head_ref, char *new_local, char *new_activity, char *new_date)
{
  struct date_node* new_node = (struct date_node*) malloc(sizeof(struct date_node));

  new_node->local  = (char *)malloc(strlen(new_local)+1);
  strcpy(new_node->local, new_local);

  new_node->activity = (char *)malloc(strlen(new_activity)+1);
  strcpy(new_node->activity, new_activity);

  new_node->date = (char *)malloc(strlen(new_date)+1);
  strcpy(new_node->date, new_date); 	

  new_node->next = (*head_ref);   
  (*head_ref)    = new_node;
	
}

char *consult_period_date(char *data1, char *data2){

  sqlite3_stmt  *res;
  int     error = 0;
  const char      *tail;
  char *sql=NULL;
  char *resposta;
 
  resposta = (char *)malloc(strlen("consult_period_date - Error - No data")+1);
  strcpy(resposta, "consult_period_date - Error - No data"); 	
 
  int tamanho_data1 = strlen(data1);
  int tamanho_data2 = strlen(data2);

  sql = (char *) malloc (sizeof(char *) * 50+tamanho_data1+tamanho_data2);

  sprintf(sql, "SELECT * FROM TRAIL WHERE DATA BETWEEN '%s' AND '%s'", data1, data2);

  error = sqlite3_prepare_v2(db, sql, 1000, &res, &tail);
 
  if (error != SQLITE_OK) {
     free(resposta);
     resposta = (char *)malloc(strlen("consult_period_date error - No data")+1);
     strcpy(resposta, "consult_period_date - Error - No data");
     return resposta;
  }

  while (sqlite3_step(res) == SQLITE_ROW) {
	push_date(&date_node, sqlite3_column_text(res, 0), sqlite3_column_text(res, 1), sqlite3_column_text(res, 2));
  }

  free(resposta);
  resposta = (char *)malloc(strlen("consult_period_date - Ok")+1);
  strcpy(resposta, "consult_period_date - Ok"); 	


  return resposta;

}

char *return_local_date2(struct date_node* node, int position){
	//struct date_node* node = date_node;     	
	int node_count = 0;
	char *result;

        result = (char *)malloc(strlen("return_local_date - Error - No data")+1);
  	result = strcpy(result, "return_local_date - Error - No data");
	
	while(node!=NULL){
		if (node_count == position){
			free(result);
			result = (char *)malloc(strlen(node->activity)+1);
			strcpy(result, node->local);
			return result;	
		}
		node_count++;
		node = node->next;
	}
	return result;	
}

char *return_local_date(int position){
	char *resposta = return_local_date2(date_node, position);
	return resposta;
}

char *return_activity_date2(struct date_node* node, int position){
	//struct date_node* node = date_node;     	
	int node_count = 0;
	char *result;

        result = (char *)malloc(strlen("return_activity_date - Error - No data")+1);
  	result = strcpy(result, "return_activity_date - Error - No data");
	
	while(node!=NULL){
		if (node_count == position){
			free(result);
			result = (char *)malloc(strlen(node->activity)+1);
			strcpy(result, node->activity);
			return result;
		}
		node_count++;
		node = node->next;
	}
	return result;
}

char *return_activity_date(int position){
	return_activity_date2(date_node, position);
}

char *return_date_date2(struct date_node* node, int position){
   	
	int node_count = 0;
	char *result;
        
        result = (char *)malloc(strlen("return_date_date - Error - No data")+1);
  	result = strcpy(result, "return_date_date - Error - No data");
	
	while(node!=NULL){
		if (node_count == position){
			free(result);
			result = (char *)malloc(strlen(node->date)+1);
			strcpy(result, node->date);
			return result;
		}
		node_count++;
		node = node->next;
	}
	return result;
}

char *return_date_date(int position){
	return_date_date2(date_node, position);
}

int queue_date_size(){
   queue_date_size2(date_node);
}

int queue_date_size2(struct date_node* node){

	int count = -1;

	while(node!=NULL){
		count++;
		node=node->next;
	}	
	
	return count;
}

char *lcl1 = NULL;
char *date1 = NULL;

int find_activity(char *local, char *date){

  sqlite3_stmt  *res;
  int     error = 0;
  const char      *errMSG;
  const char      *tail;
  char *sql=NULL;
  int count_lines = -1;	
  
  int tamanho_data1 = strlen(local);
  int tamanho_data2 = strlen(date);

  sql = (char *) malloc (sizeof(char *) * 50+tamanho_data1+tamanho_data2);

  sprintf(sql, "SELECT * FROM TRAIL WHERE LOCAL='%s' AND DATA LIKE '%s%s%s'", local,"%",date,"%");

  error = sqlite3_prepare_v2(db, sql, 1000, &res, &tail);
 
  if (error != SQLITE_OK) {
      return count_lines;
  }

  lcl1 = (char *)malloc(strlen(local)+1);
  lcl1 = strcpy(lcl1, local);

  date1 = (char *)malloc(strlen(date)+1);
  date1 = strcpy(date1, date);	

  while (sqlite3_step(res) == SQLITE_ROW) {
       //printf("activity: %s \n", sqlite3_column_text(res, 1));
       count_lines++;
  }
  return count_lines;
}

char *return_activity(int position){

  sqlite3_stmt  *res;
  int     error = 0;
  const char      *tail;
  char *sql=NULL;
  int count_lines = 0;
  char *resultado;

  resultado = (char *)malloc(strlen("return_activity - Error - No data")+1);
  resultado = strcpy(resultado, "return_activity - Error - No data");
  
  int tamanho_lcl1 = strlen(lcl1);
  int tamanho_date1 = strlen(date1);

  sql = (char *) malloc (sizeof(char *) * 50+tamanho_lcl1+tamanho_date1);

  sprintf(sql, "SELECT * FROM TRAIL WHERE LOCAL='%s' AND DATA LIKE '%s%s%s'", lcl1,"%",date1,"%");

  error = sqlite3_prepare_v2(db, sql, 1000, &res, &tail);
 
  if (error != SQLITE_OK) {
	return resultado;
  }
    
  while (sqlite3_step(res) == SQLITE_ROW) {
  	if (position == count_lines){
		free(resultado);
		resultado = (char *)malloc(strlen(sqlite3_column_text(res, 1))+1);
		resultado = strcpy(resultado, sqlite3_column_text(res, 1));
	}
       count_lines++;
  }
  return resultado;
}

int size_preferred_list(){

struct node* node_count = activities;
int count = -1;
	while(node_count!=NULL){
		count++;
		node_count = node_count->next;
	}
return count;

}

char *get_activity_pos(int pos){

struct node* node_count = activities;
char *result=NULL;
int count = 0;
	while(node_count!=NULL){
		if (pos == count){
			result = (char *)malloc(strlen(node_count->activity)+1);
			strcpy(result, node_count->activity);
			return result;
		}
		node_count = node_count->next;
		count++;
	}

result = (char *)malloc(strlen("Error - No data")+1);
strcpy(result, "Error - No data");
return result;

}

//manipulacao da data

char *dat1 = NULL;
char *dat2 = NULL;

int consult_period_date2(char *date1, char *date2){

  sqlite3_stmt  *res;
  int     error = 0;
  const char      *tail;
  char *sql=NULL;
  int count_lines = -1;	 	
  
  int tamanho_data1 = strlen(date1);
  int tamanho_data2 = strlen(date2);
  
  if (dat1==NULL){ //se dat1 estiver null, alocar normalmente, casa contrário, limpar o ponteiro e entao alocar
  	dat1 = (char *)malloc(tamanho_data1+1);
  	strcpy(dat1, date1);
  }else{
       free(dat1);
       dat1 = NULL;
       dat1 = (char *)malloc(tamanho_data1+1);
       strcpy(dat1, date1); 	
  }		

  if (dat2==NULL){
  	dat2 = (char *)malloc(tamanho_data2+1);
  	strcpy(dat2, date2);
  }else{
       free(dat2);
       dat2 = NULL;
       dat2 = (char *)malloc(tamanho_data2+1);
       strcpy(dat2, date2); 	
  }

  sql = (char *) malloc (sizeof(char *) * 52+tamanho_data1+tamanho_data2);

  sprintf(sql, "SELECT * FROM TRAIL WHERE DATA BETWEEN '%s' AND '%s'", dat1, dat2);

  error = sqlite3_prepare_v2(db, sql, 1000, &res, &tail);
 
  if (error != SQLITE_OK) {
      return count_lines;
  }

  while (sqlite3_step(res) == SQLITE_ROW) {
    count_lines++;
  }

   return count_lines;
}

char *return_period_date_local(int position){
  sqlite3_stmt  *res;
  int     error = 0;
  const char      *tail;
  char *sql=NULL;
  int count_lines = 0;
  char *resultado = NULL;	 	
  
  resultado = (char *)malloc(strlen("return_period_date_local - Error - No data")+1);
  strcpy(resultado, "return_period_date_local - Error - No data");

  int tamanho_data1 = strlen(dat1);
  int tamanho_data2 = strlen(dat2);

  sql = (char *) malloc (sizeof(char *) * 52+tamanho_data1+tamanho_data2);

  sprintf(sql, "SELECT * FROM TRAIL WHERE DATA BETWEEN '%s' AND '%s'", dat1, dat2);
	
  error = sqlite3_prepare_v2(db, sql, 1000, &res, &tail);
 
  if (error != SQLITE_OK) {
      return resultado;
  }

  
  while (sqlite3_step(res) == SQLITE_ROW) {
    
    if (position == count_lines){
	  free(resultado);
          resultado = (char *)malloc(strlen(sqlite3_column_text(res, 0))+1);
          strcpy(resultado, sqlite3_column_text(res, 0));
	  return resultado;
    }
    count_lines++;
  }

   return resultado;
}	

char *return_period_date_activity(int position){
  sqlite3_stmt  *res;
  int     error = 0;
  const char      *tail;
  char *sql=NULL;
  int count_lines = 0;
  char *resultado = NULL;	 	
  
  resultado = (char *)malloc(strlen("return_period_date_activity - Error - No data")+1);
  strcpy(resultado, "return_period_date_activity - Error - No data");

  int tamanho_data1 = strlen(dat1);
  int tamanho_data2 = strlen(dat2);

  sql = (char *) malloc (sizeof(char *) * 52+tamanho_data1+tamanho_data2);

  sprintf(sql, "SELECT * FROM TRAIL WHERE DATA BETWEEN '%s' AND '%s'", dat1, dat2);
	
  error = sqlite3_prepare_v2(db, sql, 1000, &res, &tail);
 
  if (error != SQLITE_OK) {
      return resultado;
  }

  
  while (sqlite3_step(res) == SQLITE_ROW) {
    
    if (position == count_lines){
	  free(resultado);
	  resultado = (char *)malloc(strlen(sqlite3_column_text(res, 1))+1);
          strcpy(resultado, sqlite3_column_text(res, 1));
	  return resultado;
    }
    count_lines++;
  }

   return resultado;
}	

char *return_period_date_date(int position){
  sqlite3_stmt  *res;
  int     error = 0;
  const char      *tail;
  char *sql=NULL;
  int count_lines = 0;
  char *resultado = NULL;	 	
  
  resultado = (char *)malloc(strlen("return_period_date_date - Error - No data")+1);
  strcpy(resultado, "return_period_date_date - Error - No data");

  int tamanho_data1 = strlen(dat1);
  int tamanho_data2 = strlen(dat2);

  sql = (char *) malloc (sizeof(char *) * 52+tamanho_data1+tamanho_data2);

  sprintf(sql, "SELECT * FROM TRAIL WHERE DATA BETWEEN '%s' AND '%s'", dat1, dat2);
	
  error = sqlite3_prepare_v2(db, sql, 1000, &res, &tail);
 
  if (error != SQLITE_OK) {
      return resultado;
  }

  
  while (sqlite3_step(res) == SQLITE_ROW) {
    
    if (position == count_lines){
	  free(resultado);
	  resultado = (char *)malloc(strlen(sqlite3_column_text(res, 2))+1);
          strcpy(resultado, sqlite3_column_text(res, 2));
	  return resultado;
    }
    count_lines++;
  }

   return resultado;
}

int return_number_records(){

 sqlite3_stmt  *res;
 int     error = 0;
 const char      *tail;
 int count_lines = -1;

 error = sqlite3_prepare_v2(db, "select * from trail", 1000, &res, &tail);
 
 if (error != SQLITE_OK) {
     return count_lines;
 }

  while (sqlite3_step(res) == SQLITE_ROW) {
       count_lines++;
  }

  return count_lines;
}

char *return_consult_local(int position){

 sqlite3_stmt  *res;
 int     error = 0;
 const char      *tail;
 int count_lines = 0;
 char *result = NULL;

 result = (char *)malloc (strlen("return_local - Error - No data")+1);
 strcpy(result, "return_local - Error - No data");	

 error = sqlite3_prepare_v2(db, "select * from trail", 1000, &res, &tail);
 
 if (error != SQLITE_OK) {
     return result;
 }

  while (sqlite3_step(res) == SQLITE_ROW) {
      if (position == count_lines){
	 free(result);
	 result = (char *)malloc(strlen(sqlite3_column_text(res, 0))+1);
         strcpy(result, sqlite3_column_text(res, 0));
	 return result;
      }           
      count_lines++;
  }

  return result;
}

char *return_consult_activity(int position){

 sqlite3_stmt  *res;
 int     error = 0;
 const char      *tail;
 int count_lines = 0;
 char *result = NULL;

 result = (char *)malloc (strlen("return_activity - Error - No data")+1);
 strcpy(result, "return_activity - Error - No data");	

 error = sqlite3_prepare_v2(db, "select * from trail", 1000, &res, &tail);
 
 if (error != SQLITE_OK) {
     return result;
 }

  while (sqlite3_step(res) == SQLITE_ROW) {
      if (position == count_lines){
	 free(result);
	 result = (char *)malloc(strlen(sqlite3_column_text(res, 1))+1);
         strcpy(result, sqlite3_column_text(res, 1));
	 return result;
      }           
      count_lines++;
  }

  return result;
}

char *return_consult_data(int position){

 sqlite3_stmt  *res;
 int     error = 0;
 const char      *tail;
 int count_lines = 0;
 char *result = NULL;

 result = (char *)malloc (strlen("return_data - Error - No data")+1);
 strcpy(result, "return_data - Error - No data");	

 error = sqlite3_prepare_v2(db, "select * from trail", 1000, &res, &tail);
 
 if (error != SQLITE_OK) {
     return result;
 }

  while (sqlite3_step(res) == SQLITE_ROW) {
      if (position == count_lines){
	 free(result);
	 result = (char *)malloc(strlen(sqlite3_column_text(res, 2))+1);
         strcpy(result, sqlite3_column_text(res, 2));
	 return result;
      }           
      count_lines++;
  }

  return result;
}

