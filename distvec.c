        printf("%s\n", buf);

        //Client guessed the correct numbers, close connection
        if(strcmp(buf, "Correct!") == 0){
            break;
        }

        //Client used 8 guesses, close connection
        if(strcmp(buf, "Game over") == 0){
            break;
        }
