#include <iostream>
#include <cctype>

struct Task{
	std::string text;
	struct Task *previous;
	struct Task *next;
};
struct Task* addTask(std::string task, struct Task* head);
struct Task* removeTask(int index, struct Task* head);
void printTasks(struct Task* head);

int main(){

	struct Task* head = NULL;
	bool running = true;
	int numTasks = 0;
	while(running){

		std::cout << "Commands:\n\"A\": Add Task\n\"R\": Remove Task";
		std::cout << "\n\"L\" List Tasks\n\"q\": Quit" << std::endl;
		std::cout << "Enter a commmand: ";
		std::string input;
		char command;

		std::getline(std::cin,input);
		if(input.length() != 1){
			command = 'E';
		}
		else{
			command = input[0];
		}

		switch(command){
			
			case 'A': {
				std::string task;
				std::cout << "Input task to add: ";
				std::getline(std::cin, task);
				head = addTask(task, head);
				std::cout << "\nSuccessfully added " << task << "!\n" << std::endl;
				numTasks++;
				break;
			}
			case 'R': {
				int index = 0;
				std::cout << "Input task number to remove: ";
				getline(std::cin, input);
				if(isdigit(input[0])){
					index = std::stoi(input);
					if(index >= 1 && index <= numTasks)
						head = removeTask(index, head);
				}
				else{
					std::cout << "\nError: Invalid task number.\n" << std::endl;
					break;
				}
				
				std::cout << "\nSuccessfully removed task #" << index << "!\n" << std::endl;
				break;
			}
			case 'L': {
				printTasks(head);
				break;
			}
			case 'q': running = false;
					  break;

			default: std::cout << "\nError. Invalid input.\n" << std::endl;
					  break;
		}
	}
	std::cout << "Exiting..." << std::endl;

	return 0;
}

struct Task* addTask(std::string task, struct Task* head){
	struct Task* newTask = (struct Task*) malloc(sizeof(struct Task));
	newTask->text = task;
	newTask->next = head;
	newTask->previous = NULL;
	if(head != NULL){
		head->previous = newTask;
	}
	head = newTask;
	return head;
}

struct Task* removeTask(int index, struct Task* head){
	if(head == NULL){ //Empty List
		std::cout << "\nThere are no tasks to remove.\n"<< std::endl;
	}
	else if(index == 1){ //One task in the list
		head = head->next;
	}
	else{ //Have to find the item in the list
		struct Task* tmp = head;
		int i = 0;
		while(i <= index && tmp->next != NULL){
			tmp = tmp->next;
			i++;
		}
		if(tmp->next != NULL){
			tmp->next->previous = tmp->previous;
		}
		if(tmp->previous != NULL){
			tmp->previous->next = tmp->next;
		}
		else if(tmp == NULL){
			std::cout << "\nThat task is not in the list." << std::endl;
		}
		free(tmp);
	}
	return head;
}

void printTasks(struct Task* head){
	if(head == NULL){
		std::cout << "\nThere are no tasks to list." << std::endl;
	}
	else{
		struct Task* tmp = head;
		int i = 1;
		std::cout << "\n";
		while(tmp != NULL){
			std::cout << "Task " << i << ": " << tmp->text << std::endl;
			i++;
			tmp = tmp->next;
		}	
	}
	std::cout << "\n";
}