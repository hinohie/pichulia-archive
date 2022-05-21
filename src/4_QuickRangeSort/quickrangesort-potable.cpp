// TODO : This code is WIP

using lld = long long int;
const int MAX_N = 1000000;
const int MIN_VALUE = -1000000000;
const int MAX_VALUE = 1000000000;
namespace QUICK_RANGE{
    void quick_range(int si, int ei, lld minn, lld maxx)
    {
        if(minn >= maxx)return;
        if(si == ei)return;
        if(si == ei - 1)return;
        if(si == ei - 2)
        {
            int pv = get(si);
            int qv = get(si+1);
            if(pv > qv){
                set(si, qv);
                set(si+1, pv);
            }
            return;
        }
        if(maxx == minn + 1)
        {
            // only two number exist. can we optimize here?
            int i = si;
            int j = ei - 1;
            int pv, qv;

            while(i<j){
                while(i<j)
                {
                    pv = get(i);
                    if(pv == maxx)break;
                    i++;
                }
                while(i<j){
                    qv = get(j);
                    if(qv == minn)break;
                    j--;
                }
                if(i<j){
                    set(i, minn);
                    set(j, maxx);
                    i++;
                    j--;
                }
            }
            return;
        }
        lld pivot = minn + ((lld)maxx - (lld)minn) / 2;
        int i = si;
        int j = ei - 1;
        lld pi, pj;
        lld pmin = pivot;
        lld pmax = minn;
        lld qmin = maxx;
        lld qmax = pivot;
        while(i<=j)
        {
            int psi = -1;
            while(i<=j){
                pi = get(i);
                if(pi <= pivot){
                    if(pi == pivot){
                        if(psi == -1){
                            psi = i;
                        }
                    }
                    else{
                        psi = -1;
                    }
                    i++;
                }
                else{
                    break;
                }
                pmin = min(pmin, pi);
                pmax = max(pmax, pi);
            }
            while(j>=i){
                if(j == i){
                    pj = pi;
                    if(pi == pivot && psi >= 0){
                        j = psi - 1;
                        break;
                    }
                }
                else{
                    pj = get(j);
                }
                if(pj >= pivot){
                    j--;
                }
                else{
                    break;
                }
                qmin = min(qmin, pj);
                qmax = max(qmax, pj);
            }
            if(i>=j)break;
            set(i, pj); i++;
            set(j, pi); j--;
            pmin = min(pmin, pj);
            pmax = max(pmax, pj);
            qmin = min(qmin, pi);
            qmax = max(qmax, pi);
        }
        /*
        printf("%d %d %d %d  %d\n",si, j, i, ei, pivot);
        for(int k=si; k<ei; k++){
            printf("%d ",a[k]);
        }
        printf("\n");
        */
        quick_range(si, j + 1, pmin, pmax);
        quick_range(i, ei, qmin, qmax);
    }
    void process_quick()
    {
        //printf("process range : ");
        quick_range(0, n, MIN_VALUE, MAX_VALUE);
    }
} // namespace QUICK_RANGE