/*
	Name: dataStructureLabAssessmentTask.cpp
	Copyright: 2020
	Author: Edcel Jeremy Macawili
	Date: 11/06/20 16:56
	Description: C++ program using implementations of different data structure topics.
	
	Topics used:
	Stacks (PUSH & POP Operations)
	Expression Parsing (Infix Notation)
	Queues (Enqueue Operation)
	Tree Data Structure (Heap/Heap Sort)
	Maps (Insert & Iterator Operations)
	Searching Algorithm (Linear Search)
*/

#include <iostream>
#include <stack>
#include <cstring>
#include <queue>
#include <map>
#include <windows.h>
#include <stdlib.h>
#define ROWS 10
#define COLUMNS 4
using namespace std;
// Function prototypes
void mainMenu();
void modMenu();
void userMenu();
void addGame();
void printGame();
void checkHistory();
void requestGame();
void checkGameRequest();
void heap(string array[], int n, int i);
void heapSort(string array[], int n);
void printArray(string array[], int n);
void sortByName();
void sortByYear();
void sortById();
void searchGameById();
int precedence(char op);
int applyOp(int a, int b, char op);
int evaluate(string tokens);
void downloadCalculate();
void registerAccount();
void printAccounts();
void clearDatabase();
bool accountLogin();
bool continueCheck();
// Global declaration for stacks and queues used
stack <string> gameHistory;
stack <string> gameYear;
stack <string> gameId;
stack <string> idDatabase;
queue <string> gameRequest;
map <string, string> userAccount;
// Global declaration for data structure (2D-array)
string gameList[ROWS][COLUMNS] = {
	{"Name", "ID", "Year", "Size"}
};
// Driver code
main(){
	do{
		mainMenu();
	} while (continueCheck());
}
// Function to enter user type i.e. moderator or regular user
void mainMenu(){
	char userType;
	cout << "MAIN MENU: " << endl
		<< "[A] - Moderator" << endl
		<< "[B] - Regular user" << endl
		<< "[C] - Exit program" << endl
		<< "Choice: ";
	cin >> userType;
	system("cls");
	switch (userType){
		case 'a' : case 'A' : {
			string inputPasscode;
			char modPasscode[] = "0411";
			int confirmCode;
			cout << "Enter moderator passcode: ";
			cin >> inputPasscode;
			system("cls");
			confirmCode = inputPasscode.compare(modPasscode);
			if (confirmCode == 0){
				do{
					modMenu();
				} while (continueCheck());
			}
			else {
				cout << "Passcode invalid." << endl;
			}
			break;
		}
		case 'b' : case 'B' : {
			do{
				userMenu();
			} while (continueCheck());
			break;
		}
		case 'c' : case 'C' : {
			cout << "Thank you for using this program.";
			exit(0);
			break;
		}
		default : {
			cout << "Invalid input." << endl;
			break;
		}
	}
}

void modMenu(){
	char choice;
	cout << "MOD MENU: " << endl
		<< "[A] - Add game to database" << endl
		<< "[B] - View game database" << endl
		<< "[C] - Check database history" << endl
		<< "[D] - View user account database" << endl
		<< "[E] - Clear whole database" << endl
		<< "[F] - Return to main menu" << endl
		<< "[G] - Exit program" << endl
		<< "Choice: ";
	cin >> choice;
	system("cls");
	switch (choice){
		case 'a' : case 'A' : {
			addGame();
			break;
		}
		case 'b' : case 'B' : {
			printGame();
			break;
		}
		case 'c' : case 'C' : {
			checkHistory();
			break;
		}
		case 'd' : case 'D' : {
			printAccounts();
			break;
		}
		case 'e' : case 'E' : {
			clearDatabase();
			break;
		}
		case 'f' : case 'F' : {
			mainMenu();
			break;
		}
		case 'g' : case 'G' : {
			cout << "Thank you for using this program.";
			exit(0);
			break;
		}
		default : {
			cout << "Invalid input." << endl;
			break;
		}
	}
}

void userMenu(){
	char userChoice;
	cout << "USER MENU: " << endl
		<< "[A] - Request game (Account needed)" << endl
		<< "[B] - Check request history" << endl
		<< "[C] - View game library" << endl
		<< "[D] - Search library by game ID" << endl
		<< "[E] - Download time calculator" << endl
		<< "[F] - Register an account" << endl
		<< "[G] - Return to main menu" << endl
		<< "[H] - Exit program" << endl
		<< "Choice: ";
	cin >> userChoice;
	system("cls");
	switch (userChoice){
		case 'a' : case 'A' : {
			if (userAccount.empty()){
				cout << "Register an account first." << endl;
			}
			else {
				if (accountLogin()){
					system("cls");
					requestGame();
				}
			}
			break;
		}
		case 'b' : case 'B' : {
			checkGameRequest();
			break;
		}
		case 'c' : case 'C' : {
			char sortChoice;
			cout << "Sort by: " << endl
				<< "[A] - Name" << endl
				<< "[B] - Year" << endl
				<< "[C] - ID" << endl
				<< "Choice: ";
			cin >> sortChoice;
			system("cls");
			switch (sortChoice){
				case 'a' : case 'A' : {
					sortByName();
					break;
				}
				case 'b' : case 'B' : {
					sortByYear();
					break;
				}
				case 'c' : case 'C' : {
					sortById();
					break;
				}
				default : {
					cout << "Invalid input." << endl;
					break;
				}
			}
			break;
		}
		case 'd' : case 'D' : {
			searchGameById();
			break;
		}
		case 'e' : case 'E' : {
			downloadCalculate();
			break;
		}
		case 'f' : case 'F' : {
			registerAccount();
			break;
		}
		case 'g' : case 'G' : {
			mainMenu();
			break;
		}
		case 'h' : case 'H' : {
			cout << "Thank you for using this program.";
			exit(0);
			break;
		}
		default : {
			cout << "Invalid choice." << endl;
			break;
		}
	}
}
// Function to add data to database
void addGame(){
	string temp[4];
	string yearName, idName;
	cin.ignore(INT_MAX, '\n');
	cout << "GAME DATABASE: " << endl
		<< "Enter game details: " << endl;
	for (int i = 0; i < COLUMNS; i++){
		if (i == 0){
			cout << "Name: ";
		}
		else if (i == 1){
			cout << "ID: ";
		}
		else if (i == 2){
			cout << "Year: ";
		}
		else {
			cout << "Size: ";
		}
		getline(cin, temp[i]);
	}
	// Inputs data into 2D-array
	for (int i = 0; i < ROWS; i++){
		if (gameList[i][0] == ""){
			for (int j = 0; j < COLUMNS; j++){
				gameList[i][j] = temp[j];
			}
			break;
		}
	}
	// Enters data from 2D-array into stacks as database
	gameHistory.push(temp[0]);
	yearName = temp[2] + " - " + temp[0];
	gameYear.push(yearName);
	idName = temp[1] + " - " + temp[0];
	gameId.push(idName);
	idDatabase.push(temp[1]);
}
// Prints data from 2D-array
void printGame(){
	string temp;
	cout << "GAME DATABASE: " << endl;
	for (int i = 0; i < ROWS; i++){
		for (int j = 0; j < COLUMNS; j++){
			if (gameList[i][j] != ""){
				temp = gameList[i][j];
			}
			else {
				temp = "N/A";
			}
			cout << temp << "\t";
		}
		cout << endl;
	}
}
// Prints data from stacks
void checkHistory(){
	// Uses parallel stack to duplicate data
	stack <string> tempHistory = gameHistory;
	cout << "DATABASE HISTORY: " << endl;
	if (gameHistory.empty()){
		cout << "No games have been added yet." << endl;
	}
	else {
		cout << "Sorted by game last added: " << endl;
		while (!tempHistory.empty()){
			cout << tempHistory.top() << endl;
			tempHistory.pop();
		}
	}
}
// Function to add data to queue as database
void requestGame(){
	string requestName;
	cout << "GAME REQUESTS: " << endl
		<< "Enter name of game to be requested: ";
	cin >> requestName;
	cout << "Request has been added to list." << endl;
	gameRequest.push(requestName);
}
// Prints data from queue
void checkGameRequest(){
	// Uses parallel queue to duplicate data
	queue <string> tempRequest = gameRequest;
	cout << "GAME REQUESTS: " << endl;
	if (gameRequest.empty()){
		cout << "No requests have been made yet." << endl;
	}
	else {
		for (int i = 1; !tempRequest.empty(); i++){
			cout << "Request #" << i << ": " << tempRequest.front() << endl;
			tempRequest.pop();
		}
	}
}
// Heap function
void heapify(string arr[], int n, int root){
	int largest = root;
	int left = 2*root+1;
	int right = 2*root+2;
	
	if (left < n && arr[left] > arr[largest]){
		largest = left;
	}
	if (right < n && arr[right] > arr[largest]){
		largest = right;
	}
	if (largest != root){
		swap(arr[root], arr[largest]);
		heapify(arr, n, largest);
	}
}
// Heap sort function
void heapSort(string arr[], int n){
	for (int i = n/2-1; i >= 0; i--){
		heapify(arr, n, i);
	}
	for (int i = n-1; i >= 0; i--){
		swap(arr[0], arr[i]);
		heapify(arr, i, 0);
	}
}
// Function to print sorted data from heap
void printArray(string arr[], int n){
	for (int i = 0; i < n; ++i){
		cout << arr[i] << endl;
	}
}
// Uses heap sort to sort data by name entered
void sortByName(){
	string arr[gameHistory.size()];
	// Uses parallel stack to duplicate data
	stack <string> sortHistory = gameHistory;
	cout << "GAME DATABASE: " << endl;
	if (gameHistory.empty()){
		cout << "No games have been added yet." << endl;
	}
	else {
		// Converts stack to string array
		for (int i = 0; sortHistory.size(); i++){
			arr[i] = sortHistory.top();
			sortHistory.pop();
		}
		int n = sizeof(arr) / sizeof(arr[0]);
		// Passes converted string array to heap sort function
		heapSort(arr, n);
		cout << "Sorted alphabetically: " << endl;
		printArray(arr, n);
	}
}
// Uses heap sort to sort data by year entered
void sortByYear(){
	string arr[gameYear.size()];
	// Uses parallel stack to duplicate data
	stack <string> sortYear = gameYear;
	cout << "GAME DATABASE: " << endl;
	if (gameYear.empty()){
		cout << "No games have been added yet." << endl;
	}
	else {
		// Converts stack to string array
		for (int i = 0; sortYear.size(); i++){
			arr[i] = sortYear.top();
			sortYear.pop();
		}
		int n = sizeof(arr) / sizeof(arr[0]);
		// Passes converted string array to heap sort function
		heapSort(arr, n);
		cout << "Sorted by year: " << endl;
		printArray(arr, n);
	}
}
// Uses heap sort to sort data by ID entered
void sortById(){
	string arr[gameId.size()];
	// Uses parallel stack to duplicate data
	stack <string> sortId = gameId;
	cout << "GAME DATABASE: " << endl;
	if (gameId.empty()){
		cout << "No games have been added yet." << endl;
	}
	else {
		// Converts stack to string array
		for (int i = 0; sortId.size(); i++){
			arr[i] = sortId.top();
			sortId.pop();
		}
		int n = sizeof(arr) / sizeof(arr[0]);
		// Passes converted string array to heap sort function
		heapSort(arr, n);
		cout << "Sorted by ID: " << endl;
		printArray(arr, n);
	}
}
// Linear search function
void searchGameById(){
	if (gameId.empty()){
		cout << "Game database is empty." << endl;
	}
	else {
		// Uses parallel stacks to duplicate data
		stack <string> searchId = gameId;
		stack <string> searchDatabase = idDatabase;
		string arrName[gameHistory.size()], arrId[gameId.size()], arrDatabase[idDatabase.size()];
		// Converts stack to string array
		for (int i = 0; i < idDatabase.size(); i++){
			arrId[i] = searchId.top();
			arrDatabase[i] = searchDatabase.top();
			searchId.pop();
			searchDatabase.pop();
		}
		string searchValue;
		cout << "Enter game ID to be searched: ";
		cin >> searchValue;
		for (int i = 0; i < idDatabase.size(); i++){
			if (searchValue == arrDatabase[i]){
				cout << "Game ID: " << arrId[i] << endl
					<< "Found at Index[" << i <<"]." << endl;
			}
		}
	}
}

int precedence(char op){
	if (op == '+' || op == '-'){
		return 1;
	}
	if (op == '*' || op == '/'){
		return 2;
	}
	return 0;
}

int applyOp(int a, int b, char op){
	switch(op){
		case '+' : {
			return a + b;
			break;
		}
		case '-' : {
			return a - b;
			break;
		}
		case '*' : {
			return a * b;
			break;
		}
		case '/' : {
			return a / b;
			break;
		}
	}
}

int evaluate(string tokens){
	int i;
	stack <int> values;
	stack <char> ops;
	for (i = 0; i < tokens.length(); i++){
		if (tokens[i] == ' '){
			continue;
		}
		else if (tokens[i] == '('){
			ops.push(tokens[i]);
		}
		else if (isdigit(tokens[i])){
			int val = 0;
			while(i < tokens.length() && isdigit(tokens[i])){
				val = (val * 10) + (tokens[i] - '0');
				i++;
			}
			values.push(val);
		}
		else if (tokens[i] == ')'){
			while (!ops.empty() && ops.top() != '('){
				int val2 = values.top();
				values.pop();
				int val1 = values.top();
				values.pop();
				char op = ops.top();
				ops.pop();
				
				values.push(applyOp(val1, val2, op));
			}
			if (!ops.empty()){
				ops.pop();
			}
		}
		else {
			while (!ops.empty() && precedence(ops.top()) >= precedence(tokens[i])){
				int val2 = values.top();
				values.pop();
				int val1 = values.top();
				values.pop();
				char op = ops.top();
				ops.pop();
				
				values.push(applyOp(val1, val2, op));
			}
			ops.push(tokens[i]);
		}
	}
	while (!ops.empty()){
		int val2 = values.top();
		values.pop();
		int val1 = values.top();
		values.pop();
		char op = ops.top();
		ops.pop();

		values.push(applyOp(val1, val2, op));
	}
	return values.top();
}

void downloadCalculate(){
	string fileSize, downloadSpeed, compute;
	int total, seconds, hours, minutes;
	cout << "DOWNLOAD TIME CALCULATOR: " << endl
		<< "Enter file size (in gigabytes): ";
	cin >> fileSize;
	cout << "Enter download speed (in kilobytes per second): ";
	cin >> downloadSpeed;
	compute = fileSize + " * 1024 * 1024" + " / " + downloadSpeed;
	total = evaluate(compute);
	minutes = total / 60;
	seconds = total % 60;
	hours = minutes / 60;
	minutes = minutes % 60;
	cout << "Download time: " << hours << " hours "
		<< minutes << " minutes "
		<< seconds << " seconds." << endl;
}

void registerAccount(){
	string accountUsername, accountPassword;
	cout << "ACCOUNT REGISTRATION: " << endl
		<< "Enter desired username (no spaces): ";
	cin >> accountUsername;
	cout << "Enter desired password (no spaces): ";
	cin >> accountPassword;
	if (userAccount.empty()){
		cout << "Account successfully registered." << endl;
		userAccount.insert(pair<string, string>(accountUsername, accountPassword));
	}
	else {
		map<string, string>::iterator userFind = userAccount.find(accountUsername);
		if (userFind != userAccount.end()){
			cout << "Username is taken. Try another." << endl;
		}
		else {
			cout << "Account successfully registered." << endl;
			userAccount.insert(pair<string, string>(accountUsername, accountPassword));
		}
	}
}

void printAccounts(){
	if (userAccount.empty()){
		cout << "USER ACCOUNT DATABASE: " << endl
			<< "No accounts have been registered yet." << endl;
	}
	else {
		cout << "USER ACCOUNT DATABASE: " << endl
			<< "Username\t-\tPassword" << endl;
		for (map<string, string>::iterator user = userAccount.begin(); user != userAccount.end(); user++){
			cout << user->first << "\t-\t" << user->second << endl;
		}
	}
}

void clearDatabase(){
	for (int i = 1; i < ROWS; i++){
		for (int j = 0; j < COLUMNS; j++){
			gameList[i][j] = "";
		}
	}
	while (!gameHistory.empty()){
		gameHistory.pop();
	}
	while (!gameYear.empty()){
		gameYear.pop();
	}
	while (!gameId.empty()){
		gameId.pop();
	}
	while (!idDatabase.empty()){
		idDatabase.pop();
	}
	cout << "Database cleared." << endl;
}

bool accountLogin(){
	string tempUser, tempPass;
	cout << "ACCOUNT LOGIN: " << endl
		<< "Username: ";
	cin >> tempUser;
	cout << "Password: ";
	cin >> tempPass;
	
	map<string, string>::iterator loginCheck = userAccount.find(tempUser);
	if (loginCheck == userAccount.end()){
		cout << "Account not found." << endl;
		return false;
	}
	else {
		if (loginCheck->first == tempUser && loginCheck->second == tempPass){
			return true;
		}
		else {
			cout << "Incorrect password." << endl;
			return false;
		}
	}
}

bool continueCheck(){
	char contCheck;
	cout << "-----------------------------------" << endl
		<< "Do you want to continue? (Y/N): ";
	cin >> contCheck;
	system("cls");
	switch (contCheck){
		case 'y' : case 'Y' : {
			return true;
			break;
		}
		case 'n' : case 'N' : {
			cout << "Thank you for using this program.";
			exit(0);
			break;
		}
		default : {
			cout << "Invalid input. Try again." << endl;
			return continueCheck();
			break;
		}
	}
}
