#include "filemanager.h"

FileManager :: FileManager()
{


}
 void FileManager :: set_directory(const char* dir){
     directory = dir;
 }
void FileManager :: generate_binaryFile(){
    const char* extBin = ".bin";
    std::string result = std::string(directory) +std::string(nameOfFile) + std::string(extBin);
    const char * FileNameBin = result.c_str();
    fstream fsr(FileNameBin, std::ios::out | std::ios::in | std::ios::binary );
    if(fsr){
        ofstream fe(FileNameBin); //Creamos un archivo bin nuevo para una tabla nueva si no existe
        fe.close();
        cout<<"Se creo nuevo archivo binario"<<endl;
    }
    fsr.close();
}

void FileManager :: initHeader(){

    header_buffer = calloc(1,sizeOfHeader);

    nameOfFile = (char*)header_buffer;
    sizeOfFile = (int*)(header_buffer + TABLESIZE);
    numberOfRegisters  = (int*)(header_buffer + 34);
    numberOfFreeRegisters  = (int*)(header_buffer + 38);
    ptrOfFirstRegister  = (int*)(header_buffer + 42);
    ptrToLastRegister  = (int*)(header_buffer + 46);
    ptrToFirstRegisterFree  = (int*)(header_buffer + 50);
    sizeOfRegister  = (int*)(header_buffer + 54);
    numberOfColumns  = (int*)(header_buffer + 58 );

    *nameOfFile =  ' n' ;
    *sizeOfFile = sizeOfHeader;
    *numberOfRegisters = 0;
    *numberOfFreeRegisters = 0 ;
    *ptrOfFirstRegister = nullPosition;
    *ptrToLastRegister = nullPosition;
    *ptrToFirstRegisterFree = nullPosition;
    *sizeOfRegister = 0;
    *numberOfColumns = 0;
}

void FileManager :: saveHeader(){

    const char* extBin = ".bin";
    std::string result = std::string(directory) +std::string(nameOfFile) + std::string(extBin);
    const char * FileNameBin = result.c_str();

    fstream fs(FileNameBin, std::ios::out | std::ios::in | std::ios::binary );
     if (fs){
         int temp = fs.tellp();
         fs.seekp (0, ios::beg);
         fs.write(reinterpret_cast<const char*>(header_buffer),sizeOfHeader);
         fs.seekp(temp, ios::beg);
         fs.close();
     }
     else cout<<"archivo no existe"<<" la vida"<<endl;
}

void FileManager :: loadHeader(const char * name_of_file){
    const char* extBin = ".bin";
    std::string result = std::string(directory) +std::string(name_of_file) + std::string(extBin);
    const char * FileNameBin = result.c_str();
    fstream fsr(FileNameBin, std::ios::out | std::ios::in | std::ios::binary );
    if(fsr){
        int temp = fsr.tellg();
        fsr.seekg(0,ios::beg);
        fsr.read((char*)header_buffer, sizeOfHeader);

        nameOfFile = (char*)(header_buffer) ;
        sizeOfFile =(int*)(header_buffer+ TABLESIZE);
        numberOfRegisters = (int*)(header_buffer+34);
        numberOfFreeRegisters = (int*)(header_buffer+38);
        ptrOfFirstRegister = (int*)(header_buffer+42);
        ptrToLastRegister = (int*)(header_buffer+46);
        ptrToFirstRegisterFree = (int*)(header_buffer+50);
        sizeOfRegister = (int*)(header_buffer+54);
        numberOfColumns = (int*)(header_buffer+58);


        fsr.seekg(temp,ios::beg);
    }
    else{
        cout<<"Error 001 : El archivo seleccionado no existe"<<endl;    }

   fsr.close();
}

void FileManager :: closeFile(){
    free(fileBuffer);
}

void FileManager :: saveFile(){
    const char* extBin = ".bin";
    std::string result = std::string(directory) +std::string(nameOfFile) + std::string(extBin);
    const char * FileNameBin = result.c_str();

    fstream fs(FileNameBin, std::ios::out | std::ios::in | std::ios::binary );
     if (fs){
         int temp = fs.tellp();
         fs.seekp (sizeOfHeader, ios::beg);
         fs.write(reinterpret_cast<const char*>(fileBuffer),*sizeOfFile - sizeOfHeader);
         fs.seekp(temp, ios::beg);
         fs.close();
     }
     else cout<<"archivo no existe"<<endl;

}


int* FileManager :: where(Vector3d<const char*,const char*,const char*>* condiciones ,
                          VectorRelacional<const char*,int>*op_logic){

    char* temp_register = (char*)calloc(1,*sizeOfRegister); //registro temporal para recorrer el archivo
    temp_register = (fileBuffer + (getPtrOfFirstRegister() - sizeOfHeader)) ;//obtener ultimo registro
    // areglo de enteros que contienen el numero de fila en caso de que cumpla condicion
    int* accepted_rows = new int[*numberOfRegisters];
    //por cada registro
    //solo recorro (registros usados) veces
     for(int num_row = 0; num_row < (*numberOfRegisters-*numberOfFreeRegisters) ; num_row++){

         //areglo de bools que contienen el resultado de cada condicion de izquierda a derecha
        bool* bools = new bool[condiciones->getLength()];

        Nodo3d<const char*,const char*,const char*>* nodo_temp;//se crea un nodo temporal para recorrido
        nodo_temp = condiciones->get_primerNodo();//comenzando en el primer nodo de la lista de condiciones
        condiciones->get_ultimoNodo()->set_siguiente(NULL);

        //se evalúa cada condicion, se recorre lista de condiciones
        for(int r=0 ; r< condiciones->getLength() ; r++){
            //nodo_temp->get_elemento1(), es la columna
            //nodo_temp->get_elemento2(), Es el operador "="
            // nodo_temp->get_elemento3(), Es el campo
            bools[r] = cumpleCondicion(nodo_temp->get_elemento1(),nodo_temp->get_elemento2(),
                                       nodo_temp->get_elemento3(),temp_register);
            nodo_temp = nodo_temp->get_siguiente();
        }





        bool final_bool;

        if(condiciones->getLength() > 1){

            NodoRelacional<const char*,int>* _temp;
            _temp = op_logic->get_primerNodo();
            op_logic->get_ultimoNodo()->set_siguiente(NULL);

            bool primera_vez=true;
             //ciclo para determinar si un registro cumple condiciones
            for(int f=0 ; f< op_logic->getLength() ; f++){

                //_temp->get_elemento1() es el operador el nodo de recorrido temporal de la lista de operadores
                if(compare_strings(_temp->get_elemento1(),"AND") && primera_vez){//si es la primera vez
                    final_bool = bools[f] && bools[f+1];
                    primera_vez=false;
                }
                 //_temp->get_elemento1() es el operador el nodo de recorrido temporal de la lista de operadores
                if(compare_strings(_temp->get_elemento1(),"OR")&& primera_vez){//si es la primera vez
                    final_bool = bools[f] || bools[f+1];
                    primera_vez=false;
                }
                 //_temp->get_elemento1() es el operador el nodo de recorrido temporal de la lista de operadores
                if(compare_strings(_temp->get_elemento1(),"AND") && !primera_vez){
                    final_bool = final_bool && bools[f+1];

                }
                 //_temp->get_elemento1() es el operador el nodo de recorrido temporal de la lista de operadores
                if(compare_strings(_temp->get_elemento1(),"OR")&& !primera_vez){
                    final_bool = final_bool || bools[f+1];

                }
                _temp = _temp->get_siguiente();
            }//termna cilco de verificar cond*/


        }
        else{
            final_bool = bools[0];
        }


        if(final_bool){//si cumple las condiciones que retorne el numero de fila
            accepted_rows[num_row] = num_row;
        }
        else{accepted_rows[num_row] =-1;}
        temp_register = (fileBuffer + (*(int*)(temp_register+OFFSET_PTRSIG) - sizeOfHeader)) ;//get siguiente registro
    }
    return accepted_rows;
}
bool FileManager :: cumpleCondicion(const char* columna,const char* operador , const char* campo,void* temp_register){
        int desplazamiento =  INICIO_DE_REGISTRO_EN_BYTES;     //se cuentan los 8 bytes del puntero al anteriory siguiente
        Nodo3d<const char* ,  int , int >* temp_sch; //nodo temp del schema
        temp_sch = schema.get_primerNodo();
        schema.get_ultimoNodo()->set_siguiente(NULL);
        for(int i =0 ; schema.getLength() && (temp_sch != NULL) ; i++){  //se recorre el schema
            if(compare_strings(columna,temp_sch->get_elemento1())){//se compara la columna en el schema y la columa que se quiere verificar

                if( temp_sch->get_elemento2() == STRING_ID){ //saber que tipo de dato comparar

                    char* temp_char = (char*)(temp_register + desplazamiento);
                    std::string result = std::string(temp_char);
                    const char* temp_const= result.c_str();
                    //se compara el campo que se quiere comparar contra el campo del achivo
                    if(compare_strings(temp_const,campo)){
                        //retorna true si cumple la condicion
                        return true;
                    }
                }
                else if( temp_sch->get_elemento2() == INT_ID){ //saber que tipo de dato comparar
                    //se compara el campo que se quiere comparar contra el campo del achivo
                    if(*(int*)(temp_register + desplazamiento) == atoi(campo)){
                        //retorna true si cumple la condicion
                        return true;
                    }
                }

                else if( temp_sch->get_elemento2() == FLOAT_ID){ //saber que tipo de dato comparar
                    //se compara el campo que se quiere comparar contra el campo del achivo
                    if(*(float*)(temp_register + desplazamiento) == atof(campo)){
                        //retorna true si cumple la condicion
                        return true;
                    }
                }
            }
            if(temp_sch->get_elemento2() == STRING_ID){ desplazamiento += temp_sch->get_elemento3();}// obtengo sumatoria de desplazamiento
            if(temp_sch->get_elemento2() == INT_ID){desplazamiento += BYTES_4;}// obtengo sumatoria de desplazamiento
            if(temp_sch->get_elemento2() == FLOAT_ID){desplazamiento += BYTES_4;}// obtengo sumatoria de desplazamiento
            temp_sch = temp_sch->get_siguiente(); //muevo el puntero de recorrido al siguiente
   }
        return false; //retorna false si no cumple la condicion

}

void FileManager :: printValorDeCampo(const char* columna ,int num_fila){
    char* temp_register = (char*)calloc(1,*sizeOfRegister); //registro temporal para recorrer el archivo
    temp_register = (fileBuffer + (getPtrOfFirstRegister() - sizeOfHeader)) ;//obtener ultimo registro

    for(int num_row = 0; num_row < (*numberOfRegisters-*numberOfFreeRegisters) ; num_row++){ //solo recorro (registros usados) veces
        if(num_row == num_fila){

            int desplazamiento =   INICIO_DE_REGISTRO_EN_BYTES;     //se cuentan los 4 bytes del puntero al anterior
            Nodo3d<const char* ,  int , int >* temp_sch; //nodo temp del schema
            temp_sch = schema.get_primerNodo();
            schema.get_ultimoNodo()->set_siguiente(NULL);

            for(int i =0 ; schema.getLength() && (temp_sch != NULL) ; i++){  //se recorre el schema
                if(compare_strings(columna,temp_sch->get_elemento1())){//para saber cual es la columna
                    if( temp_sch->get_elemento2() == STRING_ID){ //saber que tipo de dato guardar
                        cout<<temp_sch->get_elemento1()<<" : "<<(char*)(temp_register + desplazamiento)<<endl;
                    }
                    else if( temp_sch->get_elemento2() == INT_ID){ //saber que tipo de dato guardar
                        cout<<temp_sch->get_elemento1()<<" : "<<*(int*)(temp_register + desplazamiento)<<endl;
                    }
                    else if( temp_sch->get_elemento2() == FLOAT_ID){ //saber que tipo de dato guardar
                        cout<<temp_sch->get_elemento1()<<" : "<<*(float*)(temp_register + desplazamiento)<<endl;
                    }
                }
                if(temp_sch->get_elemento2() == STRING_ID){ desplazamiento += temp_sch->get_elemento3();}
                if(temp_sch->get_elemento2() == INT_ID){desplazamiento += BYTES_4;}// obtengo el lugar exacto donde se debe guardar los datos
                if(temp_sch->get_elemento2() == FLOAT_ID){desplazamiento += BYTES_4;}// obtengo el lugar exacto donde se debe guardar los datos
                temp_sch = temp_sch->get_siguiente();
            }
        }
        temp_register = (fileBuffer + (*(int*)(temp_register+OFFSET_PTRSIG) - sizeOfHeader)) ;//get siguiente registro
    }

}
void FileManager :: setCampo(const char* columna , const char* campo,int num_fila){

    char* temp_register = (char*)calloc(1,*sizeOfRegister); //registro temporal para recorrer el archivo
    temp_register = (fileBuffer + (getPtrOfFirstRegister() - sizeOfHeader)) ;//obtener ultimo registro

    for(int num_row = 0; num_row < (*numberOfRegisters-*numberOfFreeRegisters) ; num_row++){ //solo recorro (registros usados) veces
        if(num_row == num_fila){


            int desplazamiento =  INICIO_DE_REGISTRO_EN_BYTES;     //se cuentan los 4 bytes del puntero al anterior
            Nodo3d<const char* ,  int , int >* temp_sch; //nodo temp del schema
            temp_sch = schema.get_primerNodo();
            schema.get_ultimoNodo()->set_siguiente(NULL);

            for(int i =0 ; schema.getLength() && (temp_sch != NULL) ; i++){  //se recorre el schema
                if(compare_strings(columna,temp_sch->get_elemento1())){//para saber cual es la columna

                    if( temp_sch->get_elemento2() == STRING_ID){ //saber que tipo de dato guardar
                       // cout<<temp_sch->get_elemento1()<<" : "<<(char*)(temp_register + desplazamiento)<<endl;
                        char* temp_char = (char*)(temp_register + desplazamiento);
                        int b;
                        for(b = 0 ; campo[b] != '\0'; b++){
                            *(temp_char + b) = campo[b];
                        }
                        temp_char[b] = '\0';

                    }
                    else if( temp_sch->get_elemento2() == INT_ID){ //saber que tipo de dato guardar

                       // cout<<temp_sch->get_elemento1()<<" : "<<*(int*)(temp_register + desplazamiento)<<endl;
                        *(int*)(temp_register + desplazamiento)=atoi(campo);


                    }
                    else if( temp_sch->get_elemento2() == FLOAT_ID){ //saber que tipo de dato guardar
                        //cout<<temp_sch->get_elemento1()<<" : "<<*(float*)(temp_register + desplazamiento)<<endl;
                        *(float*)(temp_register + desplazamiento)=atof(campo);


                    }
                }
                if(temp_sch->get_elemento2() == STRING_ID){ desplazamiento += temp_sch->get_elemento3();}
                if(temp_sch->get_elemento2() == INT_ID){desplazamiento += BYTES_4;}// obtengo el lugar exacto donde se debe guardar los datos
                if(temp_sch->get_elemento2() == FLOAT_ID){desplazamiento += BYTES_4;}// obtengo el lugar exacto donde se debe guardar los datos
                temp_sch = temp_sch->get_siguiente();
            }
        }

         temp_register = (fileBuffer + (*(int*)(temp_register+OFFSET_PTRSIG) - sizeOfHeader)) ;//get siguiente registro
    }

}
void FileManager :: openFile(){
    fileBuffer = (char*)calloc(1,getSizeOfFile()-sizeOfHeader);

    const char* extBin = ".bin";
    std::string result = std::string(directory) +std::string(getNameOfFile()) + std::string(extBin);
    const char * FileNameBin = result.c_str();
    fstream fsr(FileNameBin, std::ios::out | std::ios::in | std::ios::binary );
    if(fsr){
        int temp = fsr.tellg();
        fsr.seekg(sizeOfHeader,ios::beg);
        fsr.read((char*)fileBuffer,getSizeOfFile()-sizeOfHeader );

        fsr.seekg(temp,ios::beg);
    }
    else{
        cout<<"no hay archivo"<<endl;    }

   fsr.close();
}

void FileManager :: printFile(){

    char* temp_register = (char*)calloc(1,*sizeOfRegister); //registro temporal para recorrer el archivo
    temp_register = (fileBuffer + (getPtrOfFirstRegister() - sizeOfHeader)) ;//obtener ultimo registro

   cout<<"____________________________select * From  "<<nameOfFile << "______________________________"<<endl;
   //schema.imprimirFirstRow();

   for(int num_row = 0; num_row < (*numberOfRegisters-*numberOfFreeRegisters) ; num_row++){

       cout<<"_____________________________row : "<<num_row << "______________________________"<<endl;
       int desplazamiento =   INICIO_DE_REGISTRO_EN_BYTES;     //se cuentan los 12 bytes del puntero al anterior
       Nodo3d<const char* ,  int , int >* temp_sch; //nodo temp del schema
       temp_sch = schema.get_primerNodo();
       schema.get_ultimoNodo()->set_siguiente(NULL);
      // cout<<"puntero al anterior : "<<*(int*)(temp_register)<<endl;
       //cout<<"puntero al siguiente : "<<*(int*)(temp_register + OFFSET_PTRSIG)<<endl;
       for(int i =0 ; schema.getLength() && (temp_sch != NULL) ; i++){

               if(temp_sch->get_elemento2() == STRING_ID){ //obtengo el tipo de dato

                   cout<<temp_sch->get_elemento1()<<" : "<<(char*)(temp_register + desplazamiento)<<endl;
                   desplazamiento += temp_sch->get_elemento3();// obtengo el lugar exacto donde se debe guardar los datos

               }
                else if(temp_sch->get_elemento2() == INT_ID){ //obtengo el tipo de dato

                   cout<<temp_sch->get_elemento1()<<" : "<<*(int*)(temp_register + desplazamiento)<<endl;
                   desplazamiento += BYTES_4;// obtengo el lugar exacto donde se debe guardar los datos

               }
                else if(temp_sch->get_elemento2() == FLOAT_ID){ //obtengo el tipo de dato
                   cout<<temp_sch->get_elemento1()<<" : "<<*(float*)(temp_register + desplazamiento)<<endl;
                     desplazamiento += BYTES_4;// obtengo el lugar exacto donde se debe guardar los datos

               }
           temp_sch = temp_sch->get_siguiente();
       }

       temp_register = (fileBuffer + (*(int*)(temp_register+ OFFSET_PTRSIG) - sizeOfHeader));//get siguiente registro
;
   }
   cout<<"__________________________end of Table : "<<nameOfFile << "______________________________"<<endl;
}
void FileManager :: delete_row(int num_fila){
    if(*sizeOfFile>sizeOfHeader){ //si no esta vacio
        char* temp_register = (char*)calloc(1,*sizeOfRegister); //registro temporal para recorrer el archivo
        temp_register = (fileBuffer + (getPtrOfFirstRegister() - sizeOfHeader)) ;//obtener ultimo registro
       // cout<<"____________________________delete row : "<<num_fila << "______________________________"<<endl;
        for(int num_row = 0; num_row < *numberOfRegisters - *numberOfFreeRegisters ; num_row++){ //solo recorro (registros usados) veces
            int puntero_siguiente = *(int*)(temp_register + OFFSET_PTRSIG);
            int puntero_anterior = *(int*)(temp_register);
            if(num_fila == num_row){ //si llega al que debemos eliminar
                if(puntero_siguiente == nullPosition  ){//si es el ultimo
                    setPtrToLastRegister(puntero_anterior);
                }
                else if(num_fila == 0 ){//si es el primer registro

                    setPtrOfFirstRegister(puntero_siguiente);//cambio el ptr  al ultimo registro
                }
                else{// SI EL REGISTRO A ELIMINAR NO ESTA NI AL FINAL NI AL PRINCIPIO DE LA TABLA

                    //solicito memoria para almacenar el registro antecesor y sucesor del
                    //registro en medio a eliminar
                    char* temp_siguiente_registro = (char*)calloc(1,*sizeOfRegister);
                    char* temp_anterior_registro = (char*)calloc(1,*sizeOfRegister);
                    //get registro siguiente del registro a eliminar(temp_register)
                    temp_siguiente_registro = (fileBuffer + (puntero_siguiente - sizeOfHeader)) ;
                    //get registro anterior  del registro a eliminar(temp_register)
                    temp_anterior_registro = (fileBuffer + (puntero_anterior - sizeOfHeader)) ;

                    //modifico el puntero al siguiente de temp_anterior_registro
                    //le pongo como siguiente al sucesor del que se va a eliminar(temp_register)
                    *(int*)(temp_anterior_registro+OFFSET_PTRSIG)=puntero_siguiente;

                     //modifico el puntero al anterior de temp_siguiente_registro
                    //lo desreferencio y le pongo el puntero_anterior del registroa eliminar(temp_register)
                    *(int*)temp_siguiente_registro=puntero_anterior;



                }

            }
            temp_register = (fileBuffer + (puntero_siguiente - sizeOfHeader)) ;//get siguiente
      }//fin del for
        setNumberOfFreeRegisters(getNumberOfFreeRegisters() + 1 ); //se elimino un registro
    }
}

void FileManager :: addNewRegister(void* register_buffer ){

    const char* extBin = ".bin";
    std::string result = std::string(directory) +std::string(nameOfFile) + std::string(extBin);
    const char * FileNameBin = result.c_str();

    fstream fs(FileNameBin, std::ios::out | std::ios::in | std::ios::binary );
    if(fs){
        int temp = fs.tellp();//se guarda la posicion incial del seek
         fs.seekp (0, ios::end);//se coloca el seek al final del archivo

         //si el archivo esta vacio
        if(getSizeOfFile() == sizeOfHeader){
            setPtrOfFirstRegister(sizeOfHeader);
            setPtrToLastRegister(sizeOfHeader);
        }
        else{//si el archivo tiene mas de un registro


            //se solicita espacio para el ultimo registro a del archivo
            void* ultimoReg = calloc(1, *sizeOfRegister);
            //se coloca el seek al final del archivo
            fs.seekg(getPtrToLastRegister(), ios::beg);
            fs.seekp(getPtrToLastRegister(), ios::beg);
            //se lee el ultimo registro
            fs.read((char*)ultimoReg,*sizeOfRegister);

            //se obtiene el puntero en disco al siguiente
            int* ptr_al_siguiente = (int*)(ultimoReg + OFFSET_PTRSIG);
            //al ptr siguiente se desreferencia y se pone el puntero al final
            //más el tamaño del nuevo registro
            *ptr_al_siguiente = getPtrToLastRegister()+ *sizeOfRegister;
            //se coloca el puntero seek al final del archivopara agregar al final
            fs.seekg(getPtrToLastRegister(), ios::beg);
            fs.seekp(getPtrToLastRegister(), ios::beg);
            //se escribe en disco el ultimo registro
            fs.write(reinterpret_cast<const char*>(ultimoReg),getSizeOfRegister());


            //se apunta ptr_anterior al inicio del registro
            int* ptr_anterior = (int*)register_buffer;
            //tomo el ultimo reg y antes de guardar lo pongo como anterior
            *ptr_anterior = getPtrToLastRegister();
            //actualizo puntero al ultimo registro
            setPtrToLastRegister(fs.tellp());
        }

        fs.seekp (0, ios::end);//se coloca el seek al final del archivo
        //guardo el registro al final del archivo en disco
        fs.write(reinterpret_cast<const char*>(register_buffer),getSizeOfRegister());
        setNumberOfRegisters(getNumberOfRegisters() + 1);
        fs.seekp (0, ios::end);//se coloca el seek al final del archivo
        setSizeOfFile(fs.tellp());
        fs.seekp(temp,ios::end);//se recupera el seek original

    }
    else cout<<"Error 002 :No se puede añadir registro porque archivo no existe"<<endl;

   fs.close();//cierro el objeto fstream
   free(register_buffer); //libero el espacio que soliticte para el buffer
 }


char* FileManager :: getNameOfFile(){    return nameOfFile;}
int FileManager :: getSizeOfFile(){    return *sizeOfFile;}
int FileManager :: getNumberOfRegisters(){    return *numberOfRegisters;}
int FileManager :: getNumberOfFreeRegisters(){    return *numberOfFreeRegisters;}
int FileManager :: getPtrOfFirstRegister(){    return *ptrOfFirstRegister;}
int FileManager :: getPtrToLastRegister(){    return *ptrToLastRegister;}
int FileManager :: getPtrToFirstRegisterFree(){    return *ptrToFirstRegisterFree;}
int FileManager :: getSizeOfRegister(){    return *sizeOfRegister;}
int FileManager :: getNumberOfColumns(){    return *numberOfColumns;}

void FileManager :: setNameOfFile(const char* name_of_file){
    int i;
    for(i = 0; (name_of_file[i] != '\0') && i < TABLESIZE ; i++){  //obtenemos el nombre del archivo
           *(nameOfFile+i) = name_of_file[i];
       }

    *(nameOfFile+i) = '\0' ;

}
void FileManager :: setSizeOfFile( int size_of_file){    *sizeOfFile = size_of_file;}
void FileManager :: setNumberOfRegisters(int number_of_registers){    *numberOfRegisters = number_of_registers;}
void FileManager :: setNumberOfFreeRegisters(int number_of_free_registers){    *numberOfFreeRegisters = number_of_free_registers;}
void FileManager :: setPtrOfFirstRegister(int ptr_to_first_register){    *ptrOfFirstRegister=ptr_to_first_register;}
void FileManager :: setPtrToLastRegister(int ptr_to_last_register){    *ptrToLastRegister = ptr_to_last_register;}
void FileManager :: setPtrToFirstRegisterFree(int ptr_to_first_register_free){    *ptrToFirstRegisterFree=ptr_to_first_register_free;}
void FileManager :: setSizeOfRegister(int size_of_register){    *sizeOfRegister = size_of_register;}
void FileManager :: setNumberOfColumns(int number_of_columns){    *numberOfColumns = number_of_columns;}



void FileManager :: addStringToSchema(const char* columna , int offset){
    schema.agregarAlFinal(columna,STRING_ID,offset);

}
void FileManager :: addIntToSchema(const char* columna,int offset){
    schema.agregarAlFinal(columna,INT_ID,offset);

}
void FileManager :: addFloatToSchema(const char* columna,int offset){
    schema.agregarAlFinal(columna, FLOAT_ID, offset);

}

void FileManager :: loadSchema(){
    const char* extTxt = ".txt";
    std::string result = std::string(directory) +std::string(nameOfFile) + std::string(extTxt);
    const char * schemaName = result.c_str();
    ifstream fe(schemaName);
       char cadena1[100];
       char cadena2[100];
       char cadena3[100];
       std::string temps;
       int temp2;
       int temp3;
       Vector3d<string, int, int> sch_copy;
       for(int x = 0 ; !fe.eof() && (x< *numberOfColumns)  ; x++) {
          fe >> cadena1;
          fe >> cadena2;
          fe >> cadena3;
          temps = std::string(cadena1);
          temp2 = atoi(cadena2);
          temp3 = atoi(cadena3);
        sch_copy.agregarAlFinal(temps,temp2,temp3);
       }
     Nodo3d<string,int,int>* temp;
     temp = sch_copy.get_primerNodo();
     sch_copy.get_ultimoNodo()->set_siguiente(NULL);
     for(int g = 0; g < sch_copy.getLength(); g++){
         const char* temp_c;
         temp_c = temp->get_elemento1().c_str();
         schema.agregarAlFinal(temp_c,temp->get_elemento2(),temp->get_elemento3());
         temp = temp->get_siguiente();
     }
       fe.close();
}
void FileManager :: saveSchema(){

    const char* extTxt = ".txt";
    std::string result = std::string(directory) +std::string(nameOfFile) + std::string(extTxt);
    const char * schemaName = result.c_str();
    // Crea un fichero de salida

       ofstream fe(schemaName);

       Nodo3d<const char*,int,int>* temp;
       temp = schema.get_primerNodo();
       schema.get_ultimoNodo()->set_siguiente(NULL);
       for(int x=0 ; x<(schema.getLength());x++){
           fe << temp->get_elemento1() <<endl;
           fe << temp->get_elemento2() <<endl;
           fe << temp->get_elemento3() <<endl;

           temp = temp->get_siguiente();

       }
       fe.close();
}
void FileManager :: initSchema(){
    schema.vaciar();
}
   Vector3d<const char *, int, int > FileManager :: getSchema(){
     return schema;
 }
void FileManager :: printHeader(){
    cout << "---------------------Header------------------------------------"<< endl;
      cout << "nombre de tabla : "<< getNameOfFile() << endl;
      cout << "tamaño archivo : "<< getSizeOfFile() << endl;
      cout << "num reg : "<< getNumberOfRegisters() << endl;
      cout << "num libres : "<< getNumberOfFreeRegisters() << endl;
      cout << "primer reg : "<< getPtrOfFirstRegister() << endl;
      cout << "primer libre : "<< getPtrToFirstRegisterFree() << endl;
      cout << "ultimo reg : "<< getPtrToLastRegister() << endl;
      cout << "tamañoRegistro : "<< getSizeOfRegister() << endl;
      cout << "num de columnas : "<< getNumberOfColumns() << endl;
       cout << "---------------------end-of-Header------------------------------------"<< endl;
}

bool FileManager :: compare_strings(const char* str1 , const char* str2){
    int tamanio1;
    int tamanio2;
    for(tamanio1=0 ; (str1[tamanio1] != '\0') ; tamanio1++){ }
    for(tamanio2=0 ; (str2[tamanio2] != '\0') ; tamanio2++){ }
    if(tamanio1 != tamanio2){ return false;}
    for(int x=0 ; (str1[x] != '\0') &&  (str2[x] != '\0') ; x++){
        if(str1[x] != str2[x]){
            return false;
        }
    }
    return true;
}
