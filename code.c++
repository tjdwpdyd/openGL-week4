#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>

int FlatShaded = 0;
int Wireframed = 0; // 와이어프레임 모드를 토글하기 위한 변수

int ViewX = 0, ViewY = 0; // 마우스 움직임에 따른 시점 조정 변수

void InitLight() {
    GLfloat mat_diffuse[] = { 0.5, 0.4, 0.3, 1.0 };
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_ambient[] = { 0.5, 0.4, 0.3, 1.0 };
    GLfloat mat_shininess[] = { 15.0 };
    GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat light_diffuse[] = { 0.8, 0.8, 0.8, 1.0 };
    GLfloat light_ambient[] = { 0.3, 0.3, 0.3, 1.0 };
    GLfloat light_position[] = { -3, 6, 3.0, 0.0 };

    glShadeModel(GL_SMOOTH);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
}

void MyMouseMove(GLint X, GLint Y) {
    ViewX = X;
    ViewY = Y;
    glutPostRedisplay();
}

void MyKeyboard(unsigned char key, int x, int y) {
    switch (key) {
    case 'q': case 'Q': case '\033':
        exit(0);
        break;
    case 's':
        FlatShaded = !FlatShaded;
        glShadeModel(FlatShaded ? GL_FLAT : GL_SMOOTH);
        glutPostRedisplay();
        break;
    case 'w': case 'W':
        Wireframed = !Wireframed;
        glPolygonMode(GL_FRONT_AND_BACK, Wireframed ? GL_LINE : GL_FILL);
        glutPostRedisplay();
        break;
    }
}

void DrawTable() {
    // 탁자 상판 그리기
    glBegin(GL_QUADS);
    glColor3f(0.8f, 0.52f, 0.25f); // 탁자 상판 색
    glVertex3f(-1.0f, 0.5f, -1.0f); // 왼쪽 아래
    glVertex3f(1.0f, 0.5f, -1.0f); // 오른쪽 아래
    glVertex3f(1.0f, 0.5f, 1.0f); // 오른쪽 위
    glVertex3f(-1.0f, 0.5f, 1.0f); // 왼쪽 위
    glEnd();

    // 탁자 다리 그리기
    glBegin(GL_QUADS);
    glColor3f(0.4f, 0.2f, 0.1f); // 다리 색

    // 앞 왼쪽 다리
    glVertex3f(-0.9f, 0.0f, -0.9f);
    glVertex3f(-0.7f, 0.0f, -0.9f);
    glVertex3f(-0.7f, 0.5f, -0.9f);
    glVertex3f(-0.9f, 0.5f, -0.9f);

    // 앞 오른쪽 다리
    glVertex3f(0.9f, 0.0f, -0.9f);
    glVertex3f(0.7f, 0.0f, -0.9f);
    glVertex3f(0.7f, 0.5f, -0.9f);
    glVertex3f(0.9f, 0.5f, -0.9f);

    // 뒤 왼쪽 다리
    glVertex3f(-0.9f, 0.0f, 0.9f);
    glVertex3f(-0.7f, 0.0f, 0.9f);
    glVertex3f(-0.7f, 0.5f, 0.9f);
    glVertex3f(-0.9f, 0.5f, 0.9f);

    // 뒤 오른쪽 다리
    glVertex3f(0.9f, 0.0f, 0.9f);
    glVertex3f(0.7f, 0.0f, 0.9f);
    glVertex3f(0.7f, 0.5f, 0.9f);
    glVertex3f(0.9f, 0.5f, 0.9f);
    glEnd();
}

void MyDisplay() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // 마우스에 따라 카메라 시점 조정
    gluLookAt(ViewX / 100.0, ViewY / 100.0 + 1.0, 2.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

    // 탁자와 주전자를 그림
    DrawTable();
    glPushMatrix();
    glTranslatef(0.0f, 0.7f, 0.0f); // 탁자 위에 주전자 위치 조정
    glutSolidTeapot(0.2); // 주전자를 그림
    glPopMatrix();

    glFlush();
}

void MyReshape(int w, int h) {
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-2.0, 2.0, -2.0, 2.0, -2.0, 2.0); // 탁자와 주전자를 모두 볼 수 있는 뷰 조정
}

int main(int argc, char* argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(400, 400);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("OpenGL Teapot on Table");

    glClearColor(0.4, 0.4, 0.4, 0.0);
    InitLight();
    glutDisplayFunc(MyDisplay);
    glutKeyboardFunc(MyKeyboard);
    glutMotionFunc(MyMouseMove);
    glutReshapeFunc(MyReshape);
    glutMainLoop();
}
