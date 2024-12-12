# The Game of students and candy

**The Game of students and candy** is the second part of our project of a multi-agent Game. In this game, we have a teacher wich have to stop students from getting a candy in the environnement

## Table of Contents

- [Features](#features)
- [Installation](#installation)
- [Usage](#usage)
- [Authors](#authors)

## Features

- Each student employs a unique strategy:
    - The first student will stick to the left side and follow it until reaching the candy.
    - The second student will stick to the right side, mirroring the first student's approach.
    - The third student aims to reach the candy as quickly as possible.
    - The fourth student also aims to reach the candy as quickly as possible following the shortest path.
- The teacher has its own strategy to defend the candy:
    - The teacher identifies the shortest path to reach one of the students and follows it to intercept them.

## Installation

To install the project, clone the repository to your local machine:

```bash
git clone https://github.com/DupuisThibaut/Warship-Battle.git
cd Warship-Battle
git checkout Seconde-Partie
pip install -r requirements.txt
python main.py
```

## Usage

- Once launched, the game will play and end by itself.


## Authors 
Dupuis Thibaut, Langouët Bastian, Grillot Yanis.



