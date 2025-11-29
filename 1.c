#include <stdio.h>
#include <stdlib.h>
double calculateRepayment(double loan, double interestRate, int years, double fixedInstallment);
int main() {
    printf("Welcome to Bank Loan Manager\n");
    double loan;
    printf("Please enter the amount of loan Rs: ");
    scanf("%lf", &loan);
    int years;
    printf("Please enter the duration of the loan (years): ");
    scanf("%d", &years);
    double interestRate;
    printf("Please enter the interest rate (%%) at the time of the loan: ");
    scanf("%lf", &interestRate);
    double fixedInstallment;
    printf("Please enter the amount of the fixed yearly installment: ");
    scanf("%lf", &fixedInstallment);
    double total = calculateRepayment(loan, interestRate, years, fixedInstallment);
    printf("\nTotal Repayment over %d years = Rs %.2lf\n", years, total);
    return 0;
}

double calculateRepayment(double loan, double interestRate, int years, double fixedInstallment) {
    if (loan <= 0 || years == 0) {
        return 0;
    }
    loan = loan + (loan * interestRate / 100);
    double updatedLoan = loan - fixedInstallment;
    printf("Year %d: Remaining loan = Rs %.2lf\n", (years * -1) + (years * -1) + 1, updatedLoan);
    printf("Year %d: Remaining loan = Rs %.2lf\n", years, updatedLoan);
    return fixedInstallment + calculateRepayment(updatedLoan, interestRate, years - 1, fixedInstallment);
}