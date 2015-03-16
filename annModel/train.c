#include "fann.h"
//Tommy Unger (tommyu@bu.edu)

int main(){
  const unsigned int num_input = 7;
  const unsigned int num_output = 1;
  const unsigned int num_layers = 3;
  const unsigned int num_hidden = 8;
  const float desired_error = (const float) 0.001;
  const unsigned int max_epochs = 1000;
  const unsigned int epochs_between_reports = 100;

  struct fann_train_data *data = fann_read_train_from_file("train.data");
  struct fann *ann = fann_create_standard(num_layers, num_input, num_hidden, num_output);
  int i;
  
  fann_scale_input_train_data(data, -1, 1);
  fann_shuffle_train_data(data);
  fann_set_activation_function_output(ann, FANN_SIGMOID);
  fann_type*inputData = *data->input, *outputData = *data->output;  
  for(i = 0; i < fann_length_train_data(data); i++)
    printf("in: %f \t out: %f \n", inputData[i], outputData[i]);

  printf("\nTraining now:\n");
  fann_train_on_data(ann, data, max_epochs, epochs_between_reports, desired_error);

  struct fann_train_data *data2 = fann_read_train_from_file("test.data");
  fann_type *calc_out;
  inputData = *data2->input; outputData = *data2->output;  
  fann_scale_input_train_data(data2, -1, 1);
  int wrong_male=0, wrong_female=0;
  for(i = 0; i < fann_length_train_data(data2); i++, inputData+=7){
    calc_out = fann_run(ann, inputData);
    printf("%f %f \n", inputData[0], inputData[1]);
    //    printf("%f \n", *calc_out);
    printf("out actual: %f\toutcalculated: %f \tdiff: %f  \n", outputData[i], *calc_out, (outputData[i]- *calc_out) );
    if(outputData[i] == 1 && fabs(outputData[i]- *calc_out) > 0.5)
      wrong_female++;
    if(outputData[i] == 0 && fabs(outputData[i]- *calc_out) > 0.5)
      wrong_male++;

  }

  printf("wrong_male %d, wrong_female %d\n", wrong_male, wrong_female);
  fann_destroy(ann);
  fann_destroy_train(data2);
  fann_destroy_train(data);
  return 0;
}