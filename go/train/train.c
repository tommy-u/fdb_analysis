#include "fann.h"
//Tommy Unger (tommyu@bu.edu)
#include <stdlib.h> //for exit
#define MSE
int main(int argc, char* argv[]){
  const unsigned int num_input = 51;
  const unsigned int num_output = 1;
  const unsigned int num_layers = 3;
  const unsigned int num_hidden1 = 8;
  //  const unsigned int num_hidden2 = 4;
  struct fann_train_data *data = fann_read_train_from_file("cranDB");
  fann_shuffle_train_data(data);
  printf("making train_data\n");
  struct fann_train_data *train_data = fann_subset_train_data(data,0,3252 );
  printf("making test_data\n");
  struct fann_train_data *test_data = fann_subset_train_data(data, 3252,500);
  printf("done with data \n");
  
  struct fann *ann = fann_create_standard(num_layers, num_input, num_hidden1, num_output);

  int max_epochs, epochs_between_reports = 0;
  fann_type desired_error = 0.01;

  if (argc != 2){
    printf("run with ./train <num epochs>\n");
    exit(1);
  }
  if (sscanf (argv[1], "%i", &max_epochs)!=1) { printf ("error - not an integer"); }

  int i; //, j;
  fann_type*inputData, *outputData, *calc_out;
  //  fann_set_learning_rate(ann, .3);
  //fann_scale_input_train_data(data, -1, 1);
  //fann_shuffle_train_data(data);
  //hmm

  //  fann_set_activation_function_hidden(ann, FANN_SIGMOID_SYMMETRIC);
  fann_set_activation_function_output(ann, FANN_SIGMOID_SYMMETRIC);
  
  //  printf("\nTraining now:\n");
  fann_train_on_data(ann, train_data, max_epochs, epochs_between_reports, desired_error);

  
  //  struct fann_train_data *testdata = fann_read_train_from_file("fannTest.data");
  float MSETrain = fann_test_data(ann,train_data);
  float MSETest =  fann_test_data(ann,test_data);

  inputData = *test_data->input; outputData = *test_data->output;  
  //  fann_scale_input_train_data(test_data, -1, 1);
  int wrong_male=0, wrong_female=0;
  //  printf("Epochs\tMaleErr\tFemErr\tTErr\tMSETrain\tMSETest\n");
  for(i=0; i< fann_length_train_data(test_data); i++, inputData+=51, outputData++)
    {
      calc_out = fann_run(ann, inputData);
      //        printf("act[0]=%f calc[0]=%f diff[0]=%f \n",
      //     outputData[0], calc_out[0], outputData[0]-calc_out[0]); 
      //Was Female, predicted male
      if( ( outputData[0] > 0 ) && (calc_out[0] < 0)){
	//printf("wrong, was female \n");
	  wrong_female++;
      }
      if( ( outputData[0] < 0 ) && (calc_out[0] > 0)){
	//	printf("wrong, was male \n");
	wrong_male++;
      }
    }
 
  printf("%d\t%d\t%d\t%d\t%f\t%f\n",max_epochs,  wrong_male , wrong_female , wrong_male + wrong_female, MSETrain, MSETest);
  fann_destroy_train(test_data);
  fann_save(ann, "net");
  fann_destroy(ann);
  fann_destroy_train(data);
  fann_destroy_train(train_data);

  //  printf("saving train\n");
  //  fann_save_train(train_data, "tr.d");
  //  printf("saving test\n");
  //  fann_save_train(test_data, "te.d");
  return 0;

}
