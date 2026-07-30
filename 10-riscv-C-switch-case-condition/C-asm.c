void bharath()
{
    int i = 10;
    int j = 1;

    switch (i)
    {
        case 1:
            j = j + 1;
            break;
        case 2:
            j = j + 2;
            break;
        case 3:
            j = j + 3;
        // No break statement here, so it will fall through to the next case
        default:
            j = j + 4;
    }
    return;
}