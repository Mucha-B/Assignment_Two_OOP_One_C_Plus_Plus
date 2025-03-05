/*
2. Imagine you are tasked with developing a C++ program for an online exam system used by a university.
    The system should support different types of exams, including multiple-choice exams and essay exams, each with specific attributes and behaviors.
    Additionally, the system should handle exceptions gracefully to ensure reliable exam taking.
    Your task is to design and implement this program.
        (a)	Start by designing an abstract base class called 'Exam' that represents common attributes of all exams.
            Include member variables for 'examID,' 'subject,' and 'duration.'
            Define a pure virtual function, 'gradeExam,' that should be implemented in derived classes. (3 marks)
        (b)	Create two derived classes, 'MultipleChoiceExam' and 'EssayExam,' both inheriting from the 'Exam' base class.
            Introduce attributes specific to each type of exam, such as 'questions' for 'MultipleChoiceExam' and 'topic' for 'EssayExam.' (4 marks)
        (c)	Implement constructors and destructors for each class to manage resources correctly.
            Ensure that constructors initialize member variables appropriately, and destructors release any dynamically allocated memory. (4 marks)
        (d)	Implement the 'gradeExam' function in both 'MultipleChoiceExam' and 'EssayExam' classes to simulate grading the exams.
            For 'MultipleChoiceExam,' generate random scores based on the number of correct answers, and for 'EssayExam,' implement a function that allows a grader to assign a score. (4 marks)
        (e)	Incorporate exception handling into your program to handle potential errors gracefully.
            Create custom exception classes (e.g., 'InvalidExamDurationException,' 'GradingErrorException') and handle scenarios such as invalid exam durations or errors during grading. (4 marks)
        (f)	In your main program, create instances of both 'MultipleChoiceExam' and 'EssayExam.' Simulate exam-taking and grading scenarios to test your classes and exception handling.
            Demonstrate how your program handles various exceptions. (3 marks)
        (g)	Ensure that your program provides clear and informative output, including exam details, results, and any error messages related to exception handling. (2 marks)
*/



#include <iostream>
#include <string>
#include <stdexcept>
#include <cstdlib>
#include <ctime>

using namespace std;

// Abstract base class for Exam
class Exam {
protected:
    string examID; // ID for the exam
    string subject; // Subject of the exam
    int duration; // Duration of the exam in minutes

public:
    // Constructor for Exam class to initialize ID, subject, and duration
    // Cnstructor takes in arg and we can overide the values in the child/derived/sub class
    Exam(string id, string sub, int dur){
        // this is a key word used to reference the variables with a local scope
        // We equate them to the arguments the function/constructor brings
         this->examID = id;
         this->subject = sub; 
         this->duration = dur;
        }

    // The constructor uses a member initializer list (: examID(id), subject(sub), duration(dur)) to directly initialize the member variables before entering the body.
    // This is more efficient, especially for objects like std::string, because it avoids default construction followed by assignment.
    // Exam(string id, string sub, int dur) : examID(id), subject(sub), duration(dur) {}

    // Pure virtual function for grading exams that must be implemented in derived classes
    // By overiding we change the functionality of the virtual class
    // Any class containing this function must be abstract, and any derived class must override this function to be instantiated.
    virtual void gradeExam() = 0;

    // Virtual destructor for the Exam class to allow proper cleanup of derived class objects
    virtual ~Exam() {}

    // Getter function to display the details of the exam (ID, subject, and duration)
    // Getters help us retrieve the data stored in private variables without directly calling the private variable
    void getExamDetails() const {
        cout << "Exam ID: " << examID << "\n"
             << "Subject: " << subject << "\n"
             << "Duration: " << duration << " minutes\n";
    }
};

// Custom Exception Class for invalid exam duration
// This C++ code defines a custom exception class named InvalidExamDurationException, which is used to handle invalid exam durations.
// It inherits from the standard std::exception class and overrides the what() function to provide a custom error message.
class InvalidExamDurationException : public exception {
public:
    // Override what() function to provide a custom error message when the exception is thrown
    const char* what() const noexcept override {
        return "Error: Invalid exam duration!";
    }
};

// Custom Exception Class for grading errors
class GradingErrorException : public exception {
public:
    // Override what() function to provide a custom error message when the exception is thrown
    const char* what() const noexcept override {
        return "Error: Grading process failed!";
    }
};

// Derived class for MultipleChoiceExam that inherits from base/parent/super class Exam
class MultipleChoiceExam : public Exam {
private:
    int questions; // Number of questions in the multiple choice exam

public:
    // Constructor for MultipleChoiceExam, which calls the base class constructor
    // and initializes the number of questions
    MultipleChoiceExam(string id, string sub, int dur, int q)
        : Exam(id, sub, dur), questions(q) {}

    // Override the gradeExam function to implement grading logic for MultipleChoiceExam
    void gradeExam() override {
        // In C++, the try-catch block is used for exception handling, which allows a program to detect and handle runtime errors gracefully instead of crashing.        
        // try block → Contains the code that might throw an exception.
        // catch block → Catches and handles the exception.
        try {
            // Check if the exam duration is valid, throw an exception if invalid
            // If duration is negative or zero, it is considered invalid.
            if (duration <= 0) {
                // If the condition is met, the program throws an instance of the InvalidExamDurationException class.
                // This means the program stops executing the function immediately and transfers control to the nearest catch block that can handle this exception.
                throw InvalidExamDurationException();
            }

            // Simulate grading by generating a random score between 0 and the number of questions
            // Zero being the lower limit and number of questions being the upper limit of the random number
            srand(time(0)); // Seed the random number generator with the current time
                            // srand(seed) is used to initialize the random number generator
                            // Using time(0) ensures randomness each time the program is executed
            int score = rand() % (questions + 1); // Generate a random score
                                                  // rand() generates a pseudo-random integer between 0 and RAND_MAX (a very large number, typically 32767)
                                                  // % (questions + 1) restricts the random number to the range [0, questions]
                                                  // If questions = 10, then rand() % (10 + 1) produces a number between 0 and 10 (inclusive) ensuring we stay within the range scope  

            cout << "Grading Multiple Choice Exam..." << endl;
            cout << "Score: " << score << "/" << questions << " correct answers" << endl;
        } catch (const exception& e) {
            // Catch and display any exceptions that occur during grading
            cout << e.what() << endl;
        }
    }

    // Destructor for MultipleChoiceExam (empty, as no resources are dynamically allocated)
    ~MultipleChoiceExam() {}
};

// Derived class for EssayExam that inherits from Exam
class EssayExam : public Exam {
private:
    string topic; // The essay topic

public:
    // Constructor for EssayExam, which calls the base class constructor
    // and initializes the essay topic
    // EssayExam is the constructor for this class
    // The Exam(id, sub, dur) part calls the base class constructor (from the Exam class).
    // The topic(t) part initializes the private topic member of EssayExam.
    EssayExam(string id, string sub, int dur, string t) : Exam(id, sub, dur), topic(t) {}


    // In the alternative below, the member topic is now initialized inside the constructor body instead of using : topic(t).
    // EssayExam(string id, string sub, int dur, string t) : Exam(id, sub, dur) {
    //     this->topic = t;
    // }

    // Override the gradeExam function to implement grading logic for EssayExam
    void gradeExam() override {
        // In C++, the try-catch block is used for exception handling, which allows a program to detect and handle runtime errors gracefully instead of crashing.
        // try block → Contains the code that might throw an exception.
        // catch block → Catches and handles the exception.
        try {
            // Check if the exam duration is valid, throw an exception if invalid
            // If duration is negative or zero, it is considered invalid.
            if (duration <= 0) {
                // If the condition is met, the program throws an instance of the InvalidExamDurationException class.
                // This means the program stops executing the function immediately and transfers control to the nearest catch block that can handle this exception.
                throw InvalidExamDurationException();
            }

            // Simulate grading by asking the grader to enter a score
            // Lecturer enters the score but in multiple choice, the system calculates how many questions the student got right
            int score;
            cout << "Enter score for the Essay Exam (0-100): ";
            cin >> score;

            // If the score is out of the valid range, throw a grading error exception
            if (score < 0 || score > 100) {
                throw GradingErrorException();
            }

            cout << "Grading Essay Exam..." << endl;
            cout << "Score: " << score << "/100" << endl;
        } catch (const exception& e) {
            // Catch and display any exceptions that occur during grading
            cout << e.what() << endl;
        }
    }

    // Destructor for EssayExam (empty, as no resources are dynamically allocated)
    ~EssayExam() {}
};

int main() {
    // In C++, the try-catch block is used for exception handling, which allows a program to detect and handle runtime errors gracefully instead of crashing.
        // try block → Contains the code that might throw an exception.
        // catch block → Catches and handles the exception.
    try {
        // Create a Multiple Choice Exam with ID "MC101", subject "Mathematics", duration 60 minutes, and 20 questions with one mark each
        MultipleChoiceExam mceObj("MC101", "Mathematics", 60, 20);
        mceObj.getExamDetails(); // Display the details of the exam
        mceObj.gradeExam(); // Grade the exam

        cout << "\n"; // Print a newline for separation

        // Create an Essay Exam with ID "EE101", subject "Literature", duration 90 minutes, and topic "Qunatum Computing Term Paper"
        // Structure below follows the constructor above
        // EssayExam(string id, string sub, int dur, string t)
        // id → The exam ID.
        // sub → The subject name.
        // dur → The duration of the exam.
        // t → The topic for the essay exam.
        EssayExam eeObj("EE101", "Literature", 90, "Qunatum Computing Term Paper");
        eeObj.getExamDetails(); // Display the details of the exam
        eeObj.gradeExam(); // Grade the exam

    } catch (const exception& e) {
        // Catch any general exceptions that occur and display an error message
        cout << "An error occurred: " << e.what() << endl;
    }

    return 0; // Return 0 to indicate successful execution
}
