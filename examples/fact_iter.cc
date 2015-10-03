/* Program 1: Vypocet faktorialu (iterativne) */
int main()
{
    int a;
    int vysl;
    cout << "Zadejte cislo pro vypocet faktorialu: ";
    cin >> a;
    if (a < 0) // cin nacitani zaporneho cisla nemusi podporovat
    {
        cout << "Faktorial nelze spocitat!\n";
    }
    else
    {
        vysl = 1;
        for (int foo; a > 0; a = a - 1)
        {
            vysl = vysl * a;
        }
        cout << "Vysledek je: " << vysl << "\n";
    }
    return 0;
}
