    #include <stdio.h>
    #include <raylib.h>
    #include <math.h>
    #include <stdbool.h>
    #include <time.h>
   

    struct Ball
    {
        Vector2 pos;
        float radius;
    };


    int main()
    {      
        
        struct Rectangle add_ball[10] = {0};
        Vector2 velocity = {2,5};
        SetRandomSeed((unsigned int)time(NULL));
        const int WINDOW_WIDTH = 800;
        const int WINDOW_HEIGHT = 800;
        const int GRID_SIZE = 25;
        int size = WINDOW_WIDTH / GRID_SIZE;
        int Block_rows = 10;
        int chance = 0;
        int num_of_balls =-1;

        InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Tables");
        SetTargetFPS(60);

        Rectangle table_of_squares[25][25] = {0};

        for (int i = 0; i < GRID_SIZE; i++)
                {
                    for(int j = 0; j < Block_rows; j++)
                    {
                        table_of_squares[i][j].x = i*size;
                        table_of_squares[i][j].y = j*size;
                        table_of_squares[i][j].width = size;
                        table_of_squares[i][j].height = size;
                    }
                }
        struct Rectangle Pong_left = {WINDOW_WIDTH/2-40,600,80,20};
        struct Rectangle Pong_right = {WINDOW_WIDTH/2+40,600,80,20};
        

        struct Ball ball = {{WINDOW_WIDTH/2,WINDOW_HEIGHT/2},15};

        while (!WindowShouldClose())
        {   
            
            if(IsKeyDown(KEY_LEFT))
            {
                Pong_left.x -= 10;
                Pong_right.x -= 10;
            }
            if(IsKeyDown(KEY_RIGHT))
            {
                Pong_left.x += 10;
                Pong_right.x += 10;
            }
            
            
            BeginDrawing();
                ClearBackground(RAYWHITE);
                for (int i = 0; i < GRID_SIZE; i++)
                {
                    for(int j = 0; j < Block_rows; j++)
                    {   
                        Color c ={255, 0, 0, 255}; 
                        DrawRectangleV((Vector2){table_of_squares[i][j].x,table_of_squares[i][j].y},
                        (Vector2){table_of_squares[i][j].width,table_of_squares[i][j].height},c);
                        DrawRectangleLines(table_of_squares[i][j].x,
                        table_of_squares[i][j].y,
                        table_of_squares[i][j].width,  
                        table_of_squares[i][j].height,
                        (Color){0, 0, 0, 255});
                    }
                }

                ball.pos.x -= velocity.x;
                ball.pos.y += velocity.y;

                if (ball.pos.x < 15)
                {
                    velocity.x *= -1;
                }

                if (ball.pos.x > WINDOW_WIDTH - 15)
                {
                    velocity.x *= -1;
                }

                if (ball.pos.y < 15)
                {
                    velocity.y *= 1;
                }

                if (ball.pos.y > WINDOW_HEIGHT-15)
                {
                    velocity.y *= -1;
                }
                
                for (int i = 0; i < GRID_SIZE; i++)
                {
                    for (int j = 0; j < GRID_SIZE; j++)
                    {
                        if (CheckCollisionCircleRec((Vector2){ball.pos.x,ball.pos.y},ball.radius    ,table_of_squares[i][j]))
                        {   
                            velocity.y = 5;

                            if (num_of_balls <=10)
                            {   
                                num_of_balls++;
                                add_ball[num_of_balls].x = table_of_squares[i][j].x;
                                add_ball[num_of_balls].y = table_of_squares[i][j].y;
                                add_ball[num_of_balls].width = 20;
                                add_ball[num_of_balls].height = 20;
                            }
                            
                            

                            table_of_squares[i][j].x = -100;
                            table_of_squares[i][j].y = -100;
                            chance = GetRandomValue(1,3);
                            
                            
                            
                            
                            
                        }
                        
                    }
                }


                
                
                
                if (CheckCollisionCircleRec((Vector2){ball.pos.x,ball.pos.y},ball.radius,Pong_left))
                {   
                    if (velocity.y == -2)
                    {
                        velocity.y *= -1;
                        velocity.x *= 1;
                    }
                    else
                    {
                        velocity.x *= 1;
                        velocity.y *= -1;
                    }
                    
                    
                }
                if (CheckCollisionCircleRec(ball.pos,ball.radius,Pong_right))
                {
                    if (velocity.y == -2)
                    {
                        velocity.y *= -1;
                        velocity.x *= 1;
                    }
                    else
                    {
                        velocity.x *= 1;
                        velocity.y *= -1;
                    }
                }

                if (num_of_balls >=0)
                {
                    for (int i = 0; i <= num_of_balls; i++)
                {
                    if (add_ball[num_of_balls].width == 20)
                    {
                        add_ball[num_of_balls].y +=1;
                    }

                    if (CheckCollisionRecs(Pong_left,add_ball[num_of_balls]) || CheckCollisionRecs(Pong_right,add_ball[num_of_balls]))
                    {
                        add_ball[num_of_balls].x = 0;
                        add_ball[num_of_balls].y = 0;
                        add_ball[num_of_balls].width = 0;
                        add_ball[num_of_balls].height = 0;
                    }
                    //DrawRectangleV((Vector2){add_ball[num_of_balls].x,add_ball[num_of_balls].y}
                    //,(Vector2){add_ball[num_of_balls].width,add_ball[num_of_balls].height},(Color){0,100,0,255});
                }
                }   
                
                
                
                
                
                
                DrawRectangleV((Vector2){Pong_left.x,Pong_left.y},(Vector2){Pong_left.width,Pong_left.height},(Color){0,255,0,255});
                DrawRectangleV((Vector2){Pong_right.x,Pong_right.y},(Vector2){Pong_right.width,Pong_right.height},(Color){0,100,0,255});
                
                DrawCircleV(ball.pos,ball.radius,BLUE);
            EndDrawing();

            
        }
        CloseWindow();
        return 0;
    }