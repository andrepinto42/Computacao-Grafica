# Apontamentos

Para renderizar foi necessário definir primeiro um triangulo que é feito a volta da base


``` c++

void Helper::drawBaseCilinderTriangle(float base, float radius, float angle1, float angle2)
{
glBegin(GL_TRIANGLES);
    // Define vertices in counter-clockwise (CCW) order with normal pointing out
    glVertex3f( 0.0f, base, 0.0f);
    glVertex3f(polar2CartX(radius,angle1), base, polar2CartZ(radius, angle1));
    glVertex3f(polar2CartX(radius,angle2), base, polar2CartZ(radius, angle2));
    glEnd();
}
```
Tendo esta função implementada agora é necessário um ciclo for que faça a travessia desde [0,360] dessa forma desenhando um circulo constituido por *triangulos*

*Primeira tentativa*

![](images/Screenshot%20from%202022-03-04%2010-04-49.png)

Tentei diminuir o numero de slices

*Segunda tentativa*

![](images/Screenshot%20from%202022-03-04%2010-14-01.png)


Ainda sem sucesso e com um resultado bastante estranho quando tentei desenhar apenas **5 triangulos seguidos**

O problema estava nesta funçao totalmente mal escrita
```c++

float Helper::polar2CartX(float radius,float angle)
{
    return radius * cos(angle * 180.f / M_PI);
}

float Helper::polar2CartZ(float radius, float angle)
{
    return radius * sin(angle *   180.f / M_PI);
}
```

Depois de ter sido arranjada 
* X equivale ao sin ja que é o lado oposto ao angulo
* Z equivale ao cos pois é o lado adjacente ao angulo

```c++

float Helper::polar2CartX(float radius,float angle)
{
    return radius * sin(angle * M_PI / 180.f);
}

float Helper::polar2CartZ(float radius, float angle)
{
    return radius * cos(angle *  M_PI / 180.f);
}
```
![](images/Screenshot%20from%202022-03-04%2010-17-29.png)

Resultado *Final*
![](images/Screenshot%20from%202022-03-04%2010-56-14.png)
