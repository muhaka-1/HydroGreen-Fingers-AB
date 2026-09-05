#ifndef TEST_RUNNER_H
#define TEST_RUNNER_H

#ifdef __cplusplus
extern "C" {
#endif

// ============================================================================
// MODUL: Test Runner & Verification Suite (Ansvar: Simon / QA & Test Lead)
// ============================================================================

/**
 * @brief Kör automatiserade självtester för TC-01 till TC-15 och skriver rapport till serieporten.
 */
void run_system_self_tests(void);

#ifdef __cplusplus
}
#endif

#endif // TEST_RUNNER_H
