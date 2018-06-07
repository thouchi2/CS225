/**
 * @file quadtree.h
 * Quadtree class definition.
 * @date Spring 2008
 */

#ifndef QUADTREE_H
#define QUADTREE_H

#include "png.h"

/**
 * A tree structure that is used to compress PNG images.
 */
class Quadtree
{
  public:

      Quadtree(); //default const.

      Quadtree(PNG const & source, int resolution); //Const. w/ args

      Quadtree(Quadtree const & other); //Copy const.

      ~Quadtree(); //Deconst.

      Quadtree const & operator= (Quadtree const &other); //assingment

      /**
      * MP 5.1
      */

      void buildTree(PNG const & source, int resolution);

      RGBAPixel getPixel(int x, int y) const;

      PNG decompress() const;

      /**
      *MP 5.2
      */

      void clockwiseRotate();

      void prune(int tolerance);

      int pruneSize(int tolerance) const;

      int idealPrune(int numLeaves) const;

  private:
    /**
     * A simple class representing a single node of a Quadtree.
     * You may want to add to this class; in particular, it could
     * probably use a constructor or two...
     */
    class QuadtreeNode
    {
      public:
        QuadtreeNode* nwChild; /**< pointer to northwest child */
        QuadtreeNode* neChild; /**< pointer to northeast child */
        QuadtreeNode* swChild; /**< pointer to southwest child */
        QuadtreeNode* seChild; /**< pointer to southeast child */

        RGBAPixel element; /**< the pixel stored as this node's "data" */
        int res;

        QuadtreeNode(int reso){
            res = reso;
            nwChild = NULL;
            neChild = NULL;
            swChild = NULL;
            seChild = NULL;
        }

        QuadtreeNode(QuadtreeNode * other){
            res = other->res;
            element = other->element;
        }
    };

    QuadtreeNode* root; /**< pointer to root of quadtree */

    Quadtree::QuadtreeNode* copy(QuadtreeNode *oldRoot);

    void clear(QuadtreeNode * & croot);

    void BTHelper(PNG const & source, int resolution, QuadtreeNode *croot, int x, int y);

    RGBAPixel GPHelper(int x, int y, QuadtreeNode *croot) const;

    void clockwiseRotate(QuadtreeNode * croot);

    void prune(int tol, QuadtreeNode * croot);

    bool checkTol(QuadtreeNode * croot, QuadtreeNode * croot1, int tol) const;

    int pruneSize(int tol, QuadtreeNode * croot) const;

    int idealPrune(int numLeaves, int low, int high) const;


/**** Functions for testing/grading                      ****/
/**** Do not remove this line or copy its contents here! ****/
#include "quadtree_given.h"
};

#endif
