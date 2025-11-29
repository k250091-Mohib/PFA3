#include <stdio.h>
void calculateFuel(int fuel, int consumption, int recharge, int solarBonus, int planet, int totalPlanets) {
    if (fuel <= 0) {
        printf("Planet %d: Fuel exhausted! Mission aborted.\n", planet);
        return;
    }
    if (planet > totalPlanets) {
        printf("All %d planets visited successfully with %d fuel remaining!\n", totalPlanets, fuel);
        return;
    }
    printf("Planet %d: Fuel Remaining = %d\n", planet, fuel);
    fuel -= consumption;
    if (planet % 2 == 1) {
        fuel += recharge;
        printf("  Gravitational assist: +%d fuel\n", recharge);
    }
    if (planet % 4 == 0) {
        fuel += solarBonus;
        printf("  Solar recharge: +%d fuel\n", solarBonus);
    }
    calculateFuel(fuel, consumption, recharge, solarBonus, planet + 1, totalPlanets);
}

int main() {
    int initialFuel, consumption, recharge, solarBonus, totalPlanets;
    printf("SPACECRAFT FUEL SIMULATION\n");
    printf("Enter initial fuel: ");
    scanf("%d", &initialFuel);
    printf("Enter fuel consumption per planet: ");
    scanf("%d", &consumption);
    printf("Enter gravitational assist recharge: ");
    scanf("%d", &recharge);
    printf("Enter solar recharge bonus: ");
    scanf("%d", &solarBonus);
    printf("Enter total number of planets: ");
    scanf("%d", &totalPlanets);
    printf("\nMISSION PROGRESS\n");
    calculateFuel(initialFuel, consumption, recharge, solarBonus, 1, totalPlanets);
    return 0;
}