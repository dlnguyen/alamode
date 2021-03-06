/*
 dynamical.h

 Copyright (c) 2014 Terumasa Tadano

 This file is distributed under the terms of the MIT license.
 Please see the file 'LICENCE.txt' in the root directory 
 or http://opensource.org/licenses/mit-license.php for information.
*/

#pragma once

#include "pointers.h"
#include "fcs_phonon.h"
#include <vector>
#include <complex>
#include <string>

namespace PHON_NS {

    class DistWithCell {
    public:
        int cell;
        double dist;

        DistWithCell();
        DistWithCell(const int n, const double d) {
            cell = n;
            dist = d;
        }
    };

    inline bool operator<(const DistWithCell a, const DistWithCell b) {
        return a.dist < b.dist;
    }

    class Dynamical: protected Pointers {
    public:
        Dynamical(class PHON *);
        ~Dynamical();

        void diagonalize_dynamical_all();
        void finish_dynamical();

        unsigned int neval;
        bool eigenvectors;
        bool print_eigenvectors;
        unsigned int nonanalytic;
        bool participation_ratio;

        std::string file_born;
        double na_sigma;

        double **eval_phonon;
        std::complex<double> ***evec_phonon;

        void setup_dynamical(std::string);

        // void eval_k(double *, double *, double ****, double *, std::complex<double> **, bool);
        void eval_k(double *, double *, std::vector<FcsClassExtent>, double *, std::complex<double> **, bool);
        void modify_eigenvectors();

        double fold(double);
        double freq(const double);

        void calc_participation_ratio_all(std::complex<double> ***, double**, double ***);

    private:

        void load_born();
        void calc_analytic_k(double *, std::vector<FcsClassExtent>, std::complex<double> **);
        void calc_nonanalytic_k(double *, double *, std::complex<double> **);
        void calc_nonanalytic_k2(double *, double *, std::vector<FcsClassExtent>, std::complex<double> **);

        void prepare_mindist_list(std::vector<int> **);
        void calc_atomic_participation_ratio(std::complex<double> *, double*);
        double distance(double *, double *);

        // void calc_analytic_k(double *, double ****, std::complex<double> **);
       // void modify_eigenvectors_sym();

        double **xshift_s;
        char UPLO;
        std::complex<double> ***dymat;
        double dielec[3][3];
        double ***borncharge;

        std::vector<int> **mindist_list;
    };

    extern "C" {
        void zheev_(const char *jobz, const char *uplo, int *n,	std::complex<double> *a, int *lda, 
            double *w, std::complex<double> *work, int *lwork, double *rwork, int *info);
        void zgemm_(const char *transa, const char *transb, int *m, int *n, int *k, 
            std::complex<double> *alpha, std::complex<double> *a, int *lda, std::complex<double> *b, int *ldb, 
            std::complex<double> *beta, std::complex<double> *c, int *ldc);
    }
}

