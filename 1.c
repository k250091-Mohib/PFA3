#include <stdio.h>
double calculateRepayment(double currentLoan, double interestRate, double fixedInstallment, int currentYear, int totalYears, double *totalPaid);
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
    double totalPaid = 0;
    printf("\nRepayment Schedule:\n");
    calculateRepayment(loan, interestRate, fixedInstallment, 1, years, &totalPaid);
    printf("\nTotal Repayment = Rs %.2lf\n", totalPaid);
    return 0;
}

double calculateRepayment(double currentLoan, double interestRate, double fixedInstallment, int currentYear, int totalYears, double *totalPaid) {
    if (currentLoan <= 0) {
        return 0;
    }
    if (currentYear > totalYears) {
        printf("Year %d (Extra): Remaining loan = Rs %.2lf\n", currentYear, currentLoan);
        *totalPaid += currentLoan;
        return currentLoan;
    }
    double interest = currentLoan * interestRate / 100;
    double totalDue = currentLoan + interest;
    double actualPayment;
    if (fixedInstallment >= totalDue) {
        actualPayment = totalDue;
    } else {
        actualPayment = fixedInstallment;
    }
    double remainingLoan = totalDue - actualPayment;
    *totalPaid += actualPayment;
    printf("Year %d: Remaining loan = Rs %.2lf\n", currentYear, remainingLoan);
    return actualPayment + calculateRepayment(remainingLoan, interestRate, fixedInstallment, currentYear + 1, totalYears, totalPaid);
}
