#include <iostream>
#include <sstream>
#include <string>
#include <cmath>
#include <GL/glu.h>
#include <GL/glut.h>

struct Question {
    std::string question;
    std::string choices[4];
    int correctAnswer;
};

// Polygon questions
Question polygonQuestions[10] = {
    {"How many sides does this polygon have?", {"3", "4", "5", "6"}, 3},
    {"What is the name of this polygon?", {"Triangle", "Square", "Pentagon", "Hexagon"}, 3},
    {"Which polygon has 5 sides?", {"Triangle", "Square", "Pentagon", "Hexagon"}, 2},
    {"How many vertices does this polygon have?", {"4", "5", "6", "8"}, 2},
    {"What is the name of a 4-sided polygon?", {"Triangle", "Square", "Pentagon", "Hexagon"}, 1},
    {"How many sides does a triangle have?", {"2", "3", "4", "5"}, 1},
    {"Which polygon has 4 equal sides?", {"Rectangle", "Square", "Pentagon", "Hexagon"}, 1},
    {"What is the interior angle sum of a triangle?", {"90", "180", "270", "360"}, 1},
    {"How many diagonals does a pentagon have?", {"3", "4", "5", "6"}, 1},
    {"Which polygon has the most sides?", {"Triangle", "Square", "Pentagon", "Hexagon"}, 3}
};

// General Knowledge questions
Question generalQuestions[10] = {
    {"What is the capital of Nepal?", {"Kathmandu", "Pokhara", "Lalitpur", "Bhaktapur"}, 0},
    {"Which mountain is the highest in Nepal?", {"K2", "Mount Everest", "Kangchenjunga", "Lhotse"}, 1},
    {"Which of the following is a popular festival in Nepal?", {"Diwali", "Holi", "Dashain", "Durga Puja"}, 2},
    {"Who was the first King of Nepal?", {"Prithvi Narayan Shah", "Bhaskar Shah", "Ram Shah", "Jung Bahadur Rana"}, 0},
    {"What is the national flower of Nepal?", {"Lotus", "Lily", "Rhododendron", "Sunflower"}, 2},
    {"What is the hardest natural substance on Earth?", {"Gold", "Iron", "Diamond", "Quartz"}, 2},
    {"Who is the founder of Buddhism born in Lumbini, Nepal?", {"Mahavira", "Guru Nanak", "Gautam Buddha", "Laozi"}, 2},
    {"Which city is known as the 'City of Lakes' in Nepal?", {"Kathmandu", "Pokhara", "Lalitpur", "Janakpur"}, 1},
    {"Who painted the Mona Lisa?", {"Vincent van Gogh", "Leonardo da Vinci", "Pablo Picasso", "Claude Monet"}, 1},
    {"Which element has the chemical symbol 'O'?", {"Gold", "Oxygen", "Silver", "Osmium"}, 1}
};

int currentQuestion = 0;
int selectedOption = -1;
int score = 0;
bool answered = false;
std::string userName = "";
bool enteringName = true;
bool quizTypeSelected = false;
bool isPolygonQuiz = true; // True for Polygon Quiz, False for General Knowledge

void drawBitmapString(float x, float y, void* font, const std::string& string) {
    glRasterPos2f(x, y);
    for (size_t i = 0; i < string.size(); ++i) {
        glutBitmapCharacter(font, string[i]);
    }
}

std::string intToString(int num) {
    std::stringstream ss;
    ss << num;
    return ss.str();
}

void drawBackground() {
    glBegin(GL_QUADS);
    glColor3f(0.2, 0.6, 0.2); // Background color
    glVertex2f(-1.0, -1.0);
    glVertex2f(-1.0, 1.0);
    glVertex2f(1.0, 1.0);
    glVertex2f(1.0, -1.0);
    glEnd();
}

void drawPolygon(int sides, float r, float g, float b) {
    glBegin(GL_POLYGON);
    glColor3f(r, g, b);
    for (int i = 0; i < sides; ++i) {
        glVertex2f(0.5 * cos(2 * M_PI * i / sides), 0.5 * sin(2 * M_PI * i / sides));
    }
    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    drawBackground();

    if (enteringName) {
        glColor3f(1.0, 1.0, 1.0);
        drawBitmapString(-0.5, 0.3, GLUT_BITMAP_HELVETICA_18, "Welcome to the Quiz Game!");
        drawBitmapString(-0.5, 0.1, GLUT_BITMAP_HELVETICA_18, "Please enter your name:");
        drawBitmapString(-0.5, -0.1, GLUT_BITMAP_HELVETICA_18, userName);
        drawBitmapString(-0.5, -0.3, GLUT_BITMAP_HELVETICA_18, "Press Enter to start...");
        glutSwapBuffers();
        return;
    }

    if (!quizTypeSelected) {
        glColor3f(1.0, 1.0, 1.0);
        drawBitmapString(-0.5, 0.3, GLUT_BITMAP_HELVETICA_18, "Hello, " + userName + "!");
        drawBitmapString(-0.5, 0.1, GLUT_BITMAP_HELVETICA_18, "Choose Quiz Type:");
        drawBitmapString(-0.5, -0.1, GLUT_BITMAP_HELVETICA_18, "Press 'P' for Polygon Quiz");
        drawBitmapString(-0.5, -0.2, GLUT_BITMAP_HELVETICA_18, "Press 'G' for General Knowledge Quiz");
        drawBitmapString(-0.5, -0.3, GLUT_BITMAP_HELVETICA_18, " How to play?");
        drawBitmapString(-0.5, -0.4, GLUT_BITMAP_HELVETICA_18, " Press up and down arrow to navigate through options");
        drawBitmapString(-0.5, -0.5, GLUT_BITMAP_HELVETICA_18, " Press Enter key to Select the options");

        glutSwapBuffers();
        return;
    }

    // Display questions
    Question* questions = isPolygonQuiz ? polygonQuestions : generalQuestions;
    int totalQuestions = isPolygonQuiz ? 10 : 10;

    if (currentQuestion < totalQuestions) {
        float colors[10][3] = {
            {1.0, 0.0, 0.0}, {0.0, 1.0, 0.0}, {0.0, 0.0, 1.0},
            {1.0, 1.0, 0.0}, {1.0, 0.0, 1.0}, {0.0, 1.0, 1.0},
            {0.5, 0.5, 0.5}, {0.5, 0.0, 0.5}, {1.0, 0.5, 0.0},
            {0.0, 0.5, 0.5}
        };

        if (isPolygonQuiz) {
            if (currentQuestion == 0 || currentQuestion == 1 || currentQuestion == 3 || currentQuestion == 9) {
                drawPolygon(6, colors[currentQuestion][0], colors[currentQuestion][1], colors[currentQuestion][2]);
            } else if (currentQuestion == 2 || currentQuestion == 8) {
                drawPolygon(5, colors[currentQuestion][0], colors[currentQuestion][1], colors[currentQuestion][2]);
            } else if (currentQuestion == 4 || currentQuestion == 6) {
                drawPolygon(4, colors[currentQuestion][0], colors[currentQuestion][1], colors[currentQuestion][2]);
            } else if (currentQuestion == 5 || currentQuestion == 7) {
                drawPolygon(3, colors[currentQuestion][0], colors[currentQuestion][1], colors[currentQuestion][2]);
            }
        }

        glColor3f(1.0, 1.0, 1.0);
        drawBitmapString(-0.9, 0.8, GLUT_BITMAP_HELVETICA_18, questions[currentQuestion].question);

        for (int i = 0; i < 4; ++i) {
            if (i == selectedOption) {
                glColor3f(1.0, 0.0, 0.0);
            } else {
                glColor3f(0.8, 0.8, 0.8);
            }
            drawBitmapString(-0.9, 0.5 - i * 0.2, GLUT_BITMAP_HELVETICA_18, questions[currentQuestion].choices[i]);
        }

        glColor3f(1.0, 1.0, 1.0);
       // drawBitmapString(0.7, 0.9, GLUT_BITMAP_HELVETICA_18, "Score: " + intToString(score) + "/" + intToString(totalQuestions));

        if (answered) {
            drawBitmapString(-0.9, -0.9, GLUT_BITMAP_HELVETICA_18, "Press any key to continue...");
        }
    } else {
        glColor3f(1.0, 1.0, 1.0);
        drawBitmapString(-0.9, 0.0, GLUT_BITMAP_HELVETICA_18, "Quiz completed, " + userName + "!");
        drawBitmapString(-0.9, -0.2, GLUT_BITMAP_HELVETICA_18, "Your final score: " + intToString(score) + "/" + intToString(totalQuestions));
        drawBitmapString(-0.9, -0.4, GLUT_BITMAP_HELVETICA_18, "Press 'R' to restart or 'E' to exit.");
    }

    glutSwapBuffers();
}

void keyboard(unsigned char key, int x, int y) {
    if (enteringName) {
        if (key == 13 && !userName.empty())
        { // Enter key
            enteringName = false;
            glutPostRedisplay();
        } else if (key == 8 && !userName.empty()) { // Backspace key
            userName.erase(userName.size() - 1);
            glutPostRedisplay();
        } else if (isalnum(key) || key == ' ') {
            userName += key;
            glutPostRedisplay();
        }
    } else if (!quizTypeSelected) {
        if (key == 'P' || key == 'p') {
            quizTypeSelected = true;
            isPolygonQuiz = true;
            glutPostRedisplay();
        } else if (key == 'G' || key == 'g') {
            quizTypeSelected = true;
            isPolygonQuiz = false;
            glutPostRedisplay();
        }
    } else {
        if (currentQuestion < (isPolygonQuiz ? 10 : 10) && !answered) {
            if (key == 13 && selectedOption != -1) { // Enter key
                answered = true;
                Question* questions = isPolygonQuiz ? polygonQuestions : generalQuestions;
                if (selectedOption == questions[currentQuestion].correctAnswer) {
                    score++;
                }
                glutPostRedisplay();
            }
        } else if (answered && currentQuestion < (isPolygonQuiz ? 10 : 10)) {
            currentQuestion++;
            selectedOption = -1;
            answered = false;
            glutPostRedisplay();
        } else if (key == 'r' || key == 'R') {
            // Go back to quiz selection screen
            quizTypeSelected = false;
            currentQuestion = 0;
            score = 0;
            answered = false;
            glutPostRedisplay();
        } else if (key == 'e' || key == 'E') {
            // Exit quiz
            exit(0);
        }
    }
}

void specialKeyboard(int key, int x, int y) {
    if (currentQuestion < (isPolygonQuiz ? 10 : 10) && !answered) {
        if (key == GLUT_KEY_UP) {
            selectedOption = (selectedOption + 3) % 4;
        } else if (key == GLUT_KEY_DOWN) {
            selectedOption = (selectedOption + 1) % 4;
        }
        glutPostRedisplay();
    }
}

void init() {
    glClearColor(0.2, 0.6, 0.2, 1.0);
    gluOrtho2D(-1, 1, -1, 1);
}

void timer(int value) {
    if (answered && currentQuestion < (isPolygonQuiz ? 10 : 10)) {
        currentQuestion++;
        selectedOption = -1;
        answered = false;
    }
    glutPostRedisplay();
    if (currentQuestion < (isPolygonQuiz ? 10 : 10)) {
        glutTimerFunc(1000, timer, 0);
    }
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutCreateWindow("QuizWiz");

    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(specialKeyboard);
    glutTimerFunc(0, timer, 0);

    init();

    glutMainLoop();
    return 0;
}
