#include "fann.h"
//Tommy Unger (tommyu@bu.edu)
#include <stdlib.h> //for exit

int main(int argc, char* argv[]){
  const unsigned int num_input = 7;
  const unsigned int num_output = 2;
  const unsigned int num_layers = 3;
  const unsigned int num_hidden = 8;
  struct fann_train_data *data = fann_read_train_from_file("train.data");
  struct fann *ann = fann_create_standard(num_layers, num_input, num_hidden, num_output);

  int max_epochs;
  if (argc != 2){
    printf("run with ./train <num epochs>\n");
    exit(1);
  }

  if (sscanf (argv[1], "%i", &max_epochs)!=1) { printf ("error - not an integer"); }
  int i, j;
  fann_type*inputData, *outputData, *calc_out;
  fann_set_learning_rate(ann, .5);
  fann_scale_input_train_data(data, -1, 1);
  fann_shuffle_train_data(data);
  //Keep in -1,1 range
  fann_set_activation_function_hidden(ann, FANN_SIGMOID_SYMMETRIC);
  //Outputs between 0 and 1
  fann_set_activation_function_output(ann, FANN_SIGMOID);
  
  //Define training method.
  for(j = 0; j < max_epochs; j++){
    inputData = *data->input; outputData = *data->output;
    //One full epoch
    for(i = 0; i < fann_length_train_data(data); i++, inputData+=7, outputData+=2){ 
      calc_out = fann_run(ann, inputData);

      //Female but thought male
      if( ( (outputData[0] - outputData[1]) > .99 ) && ((calc_out[0] - calc_out[1]) < 0)){
	int repFem = 0;
	for(;repFem < 2; repFem++)
	  fann_train(ann, inputData, outputData);   
      }
      else if( ( (outputData[0] - outputData[1]) < -.99 ) && ((calc_out[0] - calc_out[1]) > 0)){
	fann_train(ann, inputData, outputData);   
      }
    }
  }

  //Test with disjoint set
  struct fann_train_data *data2 = fann_read_train_from_file("test.data");
  float MSETrain = fann_test_data(ann,data);
  float MSETest =  fann_test_data(ann,data2);    
  inputData = *data2->input; outputData = *data2->output;  
  fann_scale_input_train_data(data2, -1, 1);
  int wrong_male=0, wrong_female=0;
  
  //Loop over samples
  for(i=0; i< fann_length_train_data(data2); i++, inputData+=7, outputData+=2)
    {
      calc_out = fann_run(ann, inputData);

      /*      printf("act[0]=%f act[1]=%f calc[0]=%f calc[1]=%f diff[0]=%f diff[1]=%f \n",
	      outputData[0], outputData[1], calc_out[0], calc_out[1], 
	      outputData[0]-calc_out[0], outputData[1] - calc_out[1] 
	      );
      */
      //Was Female, predicted male
      if( ( (outputData[0] - outputData[1]) > .99 ) && ((calc_out[0] - calc_out[1]) < 0)){
	//printf("wrong, was female \n");
	wrong_female++;
      }
      if( ( (outputData[0] - outputData[1]) < .99 ) && ((calc_out[0] - calc_out[1]) > 0)){
	//	printf("wrong, was male \n");
	wrong_male++;
      }
    }
 
  printf("epochs %d w_m %d W_f %d w_tot %d MSETr %f MSETe %f \n",max_epochs,  wrong_male , wrong_female , wrong_male + wrong_female, MSETrain, MSETest);


  fann_destroy(ann);
  fann_destroy_train(data2);
  fann_destroy_train(data);
  return 0;
}
