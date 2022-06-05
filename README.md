We have two files, one with the book list and the other for the user list.
A book is a structure composed of :
-an identification number, 
-a title
-an author
-a category (science, litterature, history)
-an availability status(available or unavailable) 
An user is also a structure composed of :
-a loggin
-à password
-a role (student/teacher)
-a list of the borrow books 

Initially, the program offers the user if he wants:
 -to log in
 -create a new account
 -leave

The user then enters the number of the proposal he wants to execute.
 -if the user taps 1, the program executes the function connexion
 -if the user taps 2, the program executes the "write_user" function
 -if the user taps 3, it quits the program

The "write_user" function allows the user to enter their data (a logging, a password and their role) and will then add the new user to the list of existing users.  WARNING!  the user's login must not contain any accents or spaces. The password is a PIN code, so it must only contain numbers, else it will generates a problem.

The "connexion" function allows the user to enter his loggin and then his password. The function checks if the account exists and if the connexion informations are good. Once the verification is made, the user "accesses" to his profile and the program then proposes to him if he wants to: 
-borrow a book 
- return a book 
-add a book
-change user 
-quit the program 
the user again taps the number of the proposal he wants to execute. 
-If the user taps 1, the program runs the Borrow_book 
-If the user taps 2, the program runs the return_book function

The "Borrow_book" function will display in the terminal the list of books as follows: NUM Identification/Title/ Author/ Category/ Availability. The user must captures the identification number of the book he wants to borrow. Once the action is executed, the files are rest. In the library file, the borrowed book goes from "Available" to "unavailable" and in the Users file, the book is added to the list of those borrowed by the user. Each role is allowed to borrow a maximum of 4 books 

The "Return_book" function displays in the terminal the list of books borrowed by the user. The user entered then the identification number of the book he wants to return. Once the action is executed, the files are rest. In the library file, the borrowed book goes from "unavailable" to "available", and in the user file the book is removed from the list of those borrowed by the user.

The "Add_Book" function only runs if the user is a teacher. The user entered the title, the author and the category of the work he wants to add to the list. The identification number and the availability are entered by the program. Once the action is executed, the file containing the list of books is built up. WARNING ! When the user entered the title and the author of the book, it must not contain any focus or space! Otherwise there are unknown characters problems.
The Time function is present, it work but we didn't have time to add it to the program so it is not functional at the same time as the entire program.
