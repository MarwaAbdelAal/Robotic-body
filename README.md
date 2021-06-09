# Robotic Body and Camera movement

It was a team project done by:

[Kareem Mostafa](https://github.com/KareemYaseen), 
[Marwa Abdelaal](https://github.com/MarwaAbdelAal), 
[Nada Ezzat](https://github.com/nadaezzat-99), 
[Noura Mahmoud](https://github.com/Noura-Mahmoud), 
[Youssef Mohamed](https://github.com/Youssef-elkeheil)

***

## Steps

</br>

1. **head :** </br></br>
We used `glutWireSphere` function to create a wired sphere.</br></br>
2. **Body :** </br></br>
* All other Parts of  the body were made by `glutWireCube`.</br>
* The main difference between them is the Scale and the Rotation.</br></br>
3. **Rotaion :**</br></br>
* We used `glRotatef` for rotation.</br>
* For every part we made a variable for the angle of rotation.</br>
* Arms are connected together they rotate with the same key.</br></br>

4. **Keyboard :**</br></br>
    * Shoulders :</br></br>
    `q` and `Q` : rotate around Z axis.</br>
    ![image info](images/q.jpeg)</br>
    `w` and `W` : rotate around Y axis.</br></br>
    ![image info](images/w.jpeg)</br>

    * Elbows :</br></br>
    `e` and `E` : rotate around Z axis.</br></br>
    ![image info](images/e.jpeg)</br>
    * Fingers :</br></br>
    `f` and `F` : rotate  upper fingers around Z axis.</br>
    ![image info](images/f.jpeg)</br>
    `g` and `G` : rotate  Lower fingers around Z axis.</br></br>
    ![image info](images/g.jpeg)</br>
    * Fumer :</br></br>
    `a` and `A` : rotate  Right Fumer around X axis.</br>
    ![image info](images/a.jpeg)</br>
    `s` and `S` : rotate  Right Fumer around Z axis.</br>
    ![image info](images/s.jpeg)</br>
    `z` and `Z` : rotate  Left Fumer around X axis.</br>
    ![image info](images/z.jpeg)</br>
    `x` and `X` : rotate  Left Fumer around Z axis.</br></br>
    ![image info](images/x.jpeg)</br>
    * Tibia :</br></br>
    `d` and `D` : rotate  Right Tibia around X axis.</br>
    ![image info](images/d.jpeg)</br>
    `c` and `C` : rotate  Left Tibia around X axis.</br></br>
    ![image info](images/c.jpeg)</br>
    * Camera : </br></br>
    `Left Arrow` : rotate Left</br>
    ![image info](images/left.jpeg)</br>
    `Right Arrow` : rotate Right</br>
    ![image info](images/right.jpeg)</br>
    `Up Arrow` : rotate Up</br>
    ![image info](images/up.jpeg)</br>
    `Down Arrow` : rotate down</br>
    ![image info](images/down.jpeg)</br>
    `1` : Zoom in</br>
    ![image info](images/zi.jpeg)</br>
    `2` : Zoom out</br>
    ![image info](images/zo.jpeg)</br>
    `0` : reset</br></br>
    ![image info](images/0.jpeg)</br>

## Problems

</br>

 **Linking Parts :** </br></br>
Solved by using `glPushMatrix()` and `glPopMatrix()`</br></br>

## Compile 

```bash
g++ -o main main.cpp -lGL -lglut -lGLU -lm
```

## Run 

```bash
./main
```
