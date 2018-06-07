/**
 * @file kdtree.cpp
 * Implementation of KDTree class.
 */

template <int Dim>
bool KDTree<Dim>::smallerDimVal(const Point<Dim>& first,
                                const Point<Dim>& second, int curDim) const
{
    /**
     * @todo Implement this function!
     */
    double f = first[curDim];
    double s = second[curDim];
    if(f <= s)
        return true;
    return false;
}

template <int Dim>
bool KDTree<Dim>::shouldReplace(const Point<Dim>& target,
                                const Point<Dim>& currentBest,
                                const Point<Dim>& potential) const
{
    /**
     * @todo Implement this function!
     */
     double pot = getDistance(potential, target);
     double curr = getDistance(currentBest, target);
     if(pot == curr)
        return potential < currentBest;
    return pot < curr;
}

template <int Dim>
int KDTree<Dim>::getDistance(Point<Dim> one, Point<Dim> two) const{
    int d = 0;
    for(int i = 0; i < Dim; i++)
        d += (one[i] - two[i])*(one[i] - two[i]);
    return d;
}

template <int Dim>
KDTree<Dim>::KDTree(const vector<Point<Dim>>& newPoints)
{
    /**
     * @todo Implement this function!
     */
    points = newPoints;
    buildTree(0, 0, newPoints.size()-1);
}

template <int Dim>
void KDTree<Dim>::buildTree(int dim, int l, int r){
    if(l == r)
        return;
    int mid = (l + r)/2;
    quickS(l, r, dim, mid);
    if(l < mid)
        buildTree((dim + 1) % Dim, l, mid - 1);
    if(mid < r)
        buildTree((dim + 1) % Dim, mid + 1, r);
}

template <int Dim>
void KDTree<Dim>::quickS(int l, int r, int d, int m){
    while(l < r){
        int piv = part(l, r, m, d);
        if(piv == m)
            return;
        if(m < piv)
            r = piv - 1;
        else
            l = piv + 1;
    }
}

template <int Dim>
int KDTree<Dim>::part(int l, int r, int pivIndex, int d){
    Point<Dim> temp = points[pivIndex];
    Point<Dim> piv = points[pivIndex];
    points[pivIndex] = points[r];
    points[r] = temp;
    int i = l;
    for(int j = l; j < r; j++){
        if(smallerDimVal(points[j], piv, d) || points[j] == piv){
            temp = points[i];
            points[i] = points[j];
            points[j] = temp;
            i++;
        }
    }
    temp = points[r];
    points[r] = points[i];
    points[i] = temp;
    return i;
}

template <int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(const Point<Dim>& query) const
{
    /**
     * @todo Implement this function!
     */
     Point<Dim> point = points[(points.size() - 1)/2];
     int r = points.size() - 1;
     return findNearestNeighbor(query, point, 0, 0, r);
}

template <int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(const Point<Dim> & target, const Point<Dim> & curr,int d, int l, int r) const{
    Point<Dim> retVal = curr;
    if(r == l){
        if(shouldReplace(target, curr, points[l])){
            retVal = points[l];
            return retVal;
        }
        retVal = curr;
        return retVal;
    }

    int mid = (l + r)/2;
    bool smaller = smallerDimVal(points[mid], target, d);
    if(r > mid && smaller)
        retVal = findNearestNeighbor(target, curr, (d + 1) % Dim, mid + 1, r);
    if(l < mid && !smaller)
        retVal = findNearestNeighbor(target, curr, (d + 1) % Dim, l, mid - 1);
    if(shouldReplace(target, retVal, points[mid]))
        retVal = points[mid];

    int distance = ((points[mid])[d] - target[d])*((points[mid])[d] - target[d]);
    int dist = getDistance(target, retVal);
    if(distance <= dist){
        if(r > mid)
            retVal = findNearestNeighbor(target, retVal, (d + 1) % Dim, mid + 1, r);
        if(l < mid)
            retVal = findNearestNeighbor(target, retVal, (d + 1) % Dim, l, mid - 1);
    }
    return retVal;
}
