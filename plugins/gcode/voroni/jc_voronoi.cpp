// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com
/********************************************************************************
 * Author    :  Damir Bakiev                                                    *
 * Version   :  na                                                              *
 * Date      :  March 25, 2023                                                  *
 * Website   :  na                                                              *
 * Copyright :  Damir Bakiev 2016-2023                                          *
 * License   :                                                                  *
 * Use, modification & distribution is subject to Boost Software License Ver 1. *
 * http://www.boost.org/LICENSE_1_0.txt                                         *
 *******************************************************************************/
// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com
//// INTERNAL FUNCTIONS

// #if defined(_MSC_VER) && !defined(__cplusplus)
// #define inline __inline
// #endif

//// jcv_point

// static inline int jcv_point_cmp(const void* p1, const void* p2)
//{
//     const jcv_point* s1 = (const jcv_point*)p1;
//     const jcv_point* s2 = (const jcv_point*)p2;
//     return (s1->y != s2->y) ? (s1->y < s2->y ? -1 : 1) : (s1->x < s2->x ? -1 : 1);
// }

// static inline int jcv_point_less(const jcv_point* pt1, const jcv_point* pt2)
//{
//     return (pt1->y == pt2->y) ? (pt1->x < pt2->x) : pt1->y < pt2->y;
// }

// static inline int jcv_point_eq(const jcv_point* pt1, const jcv_point* pt2)
//{
//     return (pt1->y == pt2->y) && (pt1->x == pt2->x);
// }

// static inline int jcv_point_on_box_edge(const jcv_point* pt, const jcv_point* min, const jcv_point* max)
//{
//     return pt->x == min->x || pt->y == min->y || pt->x == max->x || pt->y == max->y;
// }

// static inline jcv_real jcv_point_dist_sq(const jcv_point* pt1, const jcv_point* pt2)
//{
//     jcv_real diffx = pt1->x - pt2->x;
//     jcv_real diffy = pt1->y - pt2->y;
//     return diffx * diffx + diffy * diffy;
// }

// static inline jcv_real jcv_point_dist(const jcv_point* pt1, const jcv_point* pt2)
//{
//     return (jcv_real)(JCV_SQRT(jcv_point_dist_sq(pt1, pt2)));
// }

//// Structs

// #pragma pack(push, 1)

// typedef struct _jcv_halfedge {
//     jcv_edge* edge;
//     struct _jcv_halfedge* left;
//     struct _jcv_halfedge* right;
//     jcv_point vertex;
//     jcv_real y;
//     int direction; // 0=left, 1=right
//     int pqpos;
// } jcv_halfedge;

// typedef struct _jcv_memoryblock {
//     size_t sizefree;
//     struct _jcv_memoryblock* next;
//     char* memory;
// } jcv_memoryblock;

// typedef int (*FJCVPriorityQueuePrint)(const void* node, int pos);

// typedef struct _jcv_priorityqueue {
//     // Implements a binary heap
//     int maxnumitems;
//     int numitems;
//     void** items;
// } jcv_priorityqueue;

// struct _jcv_context_internal {
//     void* mem;
//     jcv_edge* edges;
//     jcv_halfedge* beachline_start;
//     jcv_halfedge* beachline_end;
//     jcv_halfedge* last_inserted;
//     jcv_priorityqueue* eventqueue;

//    jcv_site* sites;
//    jcv_site* bottomsite;
//    int numsites;
//    int currentsite;
//    int _padding;

//    jcv_memoryblock* memblocks;
//    jcv_edge* edgepool;
//    jcv_halfedge* halfedgepool;
//    void** eventmem;
//    jcv_clipper clipper;

//    void* memctx; // Given by the user
//    FJCVAllocFn alloc;
//    FJCVFreeFn free;

//    jcv_rect rect;
//};

// #pragma pack(pop)

// static const int JCV_DIRECTION_LEFT = 0;
// static const int JCV_DIRECTION_RIGHT = 1;
// static const jcv_real JCV_INVALID_VALUE = (jcv_real)-JCV_FLT_MAX;

// void jcv_diagrafree_(jcv_diagram* d)
//{
//     jcv_context_internal* internal = d->internal;
//     void* memctx = internal->memctx;
//     FJCVFreeFn freefn = internal->free;
//     while (internal->memblocks) {
//         jcv_memoryblock* p = internal->memblocks;
//         internal->memblocks = internal->memblocks->next;
//         freefn(memctx, p);
//     }

//    freefn(memctx, internal->mem);
//}

// const jcv_site* jcv_diagraget_sites_(const jcv_diagram* diagram)
//{
//     return diagram->internal->sites;
// }

// const jcv_edge* jcv_diagraget_edges_(const jcv_diagram* diagram)
//{
//     jcv_edge e;
//     e.next = diagram->internal->edges;
//     return jcv_diagraget_next_edge_(&e);
// }

// const jcv_edge* jcv_diagraget_next_edge_(const jcv_edge* edge)
//{
//     const jcv_edge* e = edge->next;
//     while (e != 0 && jcv_point_eq(&e->pos[0], &e->pos[1])) {
//         e = e->next;
//     }
//     return e;
// }

// static void* jcv_alloc(jcv_context_internal* internal, size_t size)
//{
//     if (!internal->memblocks || internal->memblocks->sizefree < size) {
//         size_t blocksize = 16 * 1024;
//         jcv_memoryblock* block = (jcv_memoryblock*)internal->alloc(internal->memctx, blocksize);
//         size_t offset = sizeof(jcv_memoryblock);
//         block->sizefree = blocksize - offset;
//         block->next = internal->memblocks;
//         block->memory = ((char*)block) + offset;
//         internal->memblocks = block;
//     }
//     void* p = internal->memblocks->memory;
//     internal->memblocks->memory += size;
//     internal->memblocks->sizefree -= size;
//     return p;
// }

// static jcv_edge* jcv_alloc_edge(jcv_context_internal* internal)
//{
//     return (jcv_edge*)jcv_alloc(internal, sizeof(jcv_edge));
// }

// static jcv_halfedge* jcv_alloc_halfedge(jcv_context_internal* internal)
//{
//     if (internal->halfedgepool) {
//         jcv_halfedge* edge = internal->halfedgepool;
//         internal->halfedgepool = internal->halfedgepool->right;
//         return edge;
//     }

//    return (jcv_halfedge*)jcv_alloc(internal, sizeof(jcv_halfedge));
//}

// static jcv_graphedge* jcv_alloc_graphedge(jcv_context_internal* internal)
//{
//     return (jcv_graphedge*)jcv_alloc(internal, sizeof(jcv_graphedge));
// }

// static void* jcv_alloc_fn(void* memctx, size_t size)
//{
//     (void)memctx;
//     return malloc(size);
// }

// static void jcv_free_fn(void* memctx, void* p)
//{
//     (void)memctx;
//     free(p);
// }

//// jcv_edge

// static inline int jcv_is_valid(const jcv_point* p)
//{
//     return (p->x != JCV_INVALID_VALUE || p->y != JCV_INVALID_VALUE) ? 1 : 0;
// }

// static void jcv_edge_create(jcv_edge* e, jcv_site* s1, jcv_site* s2)
//{
//     e->next = 0;
//     e->sites[0] = s1;
//     e->sites[1] = s2;
//     e->pos[0].x = JCV_INVALID_VALUE;
//     e->pos[0].y = JCV_INVALID_VALUE;
//     e->pos[1].x = JCV_INVALID_VALUE;
//     e->pos[1].y = JCV_INVALID_VALUE;

//    // Create line equation between S1 and S2:
//    // jcv_real a = -1 * (s2->p.y - s1->p.y);
//    // jcv_real b = s2->p.x - s1->p.x;
//    // //jcv_real c = -1 * (s2->p.x - s1->p.x) * s1->p.y + (s2->p.y - s1->p.y) * s1->p.x;
//    //
//    // // create perpendicular line
//    // jcv_real pa = b;
//    // jcv_real pb = -a;
//    // //jcv_real pc = pa * s1->p.x + pb * s1->p.y;
//    //
//    // // Move to the mid point
//    // jcv_real mx = s1->p.x + dx * jcv_real(0.5);
//    // jcv_real my = s1->p.y + dy * jcv_real(0.5);
//    // jcv_real pc = ( pa * mx + pb * my );

//    jcv_real dx = s2->p.x - s1->p.x;
//    jcv_real dy = s2->p.y - s1->p.y;
//    int dx_is_larger = (dx * dx) > (dy * dy); // instead of fabs

//    // Simplify it, using dx and dy
//    e->c = dx * (s1->p.x + dx * (jcv_real)0.5) + dy * (s1->p.y + dy * (jcv_real)0.5);

//    if (dx_is_larger) {
//        e->a = (jcv_real)1;
//        e->b = dy / dx;
//        e->c /= dx;
//    } else {
//        e->a = dx / dy;
//        e->b = (jcv_real)1;
//        e->c /= dy;
//    }
//}

//// CLIPPING
// int jcv_boxshape_test(const jcv_clipper* clipper, const jcv_point p)
//{
//     return p.x >= clipper->min.x && p.x <= clipper->max.x && p.y >= clipper->min.y && p.y <= clipper->max.y;
// }

//// The line equation: ax + by + c = 0
//// see jcv_edge_create
// int jcv_boxshape_clip(const jcv_clipper* clipper, jcv_edge* e)
//{
//     jcv_real pxmin = clipper->min.x;
//     jcv_real pxmax = clipper->max.x;
//     jcv_real pymin = clipper->min.y;
//     jcv_real pymax = clipper->max.y;

//    jcv_real x1, y1, x2, y2;
//    jcv_point* s1;
//    jcv_point* s2;
//    if (e->a == (jcv_real)1 && e->b >= (jcv_real)0) {
//        s1 = jcv_is_valid(&e->pos[1]) ? &e->pos[1] : 0;
//        s2 = jcv_is_valid(&e->pos[0]) ? &e->pos[0] : 0;
//    } else {
//        s1 = jcv_is_valid(&e->pos[0]) ? &e->pos[0] : 0;
//        s2 = jcv_is_valid(&e->pos[1]) ? &e->pos[1] : 0;
//    };

//    if (e->a == (jcv_real)1) // delta x is larger
//    {
//        y1 = pymin;
//        if (s1 != 0 && s1->y > pymin) {
//            y1 = s1->y;
//        }
//        if (y1 > pymax) {
//            y1 = pymax;
//        }
//        x1 = e->c - e->b * y1;
//        y2 = pymax;
//        if (s2 != 0 && s2->y < pymax)
//            y2 = s2->y;

//        if (y2 < pymin) {
//            y2 = pymin;
//        }
//        x2 = (e->c) - (e->b) * y2;
//        // Never occurs according to lcov
//        // if( ((x1 > pxmax) & (x2 > pxmax)) | ((x1 < pxmin) & (x2 < pxmin)) )
//        // {
//        //     return 0;
//        // }
//        if (x1 > pxmax) {
//            x1 = pxmax;
//            y1 = (e->c - x1) / e->b;
//        } else if (x1 < pxmin) {
//            x1 = pxmin;
//            y1 = (e->c - x1) / e->b;
//        }
//        if (x2 > pxmax) {
//            x2 = pxmax;
//            y2 = (e->c - x2) / e->b;
//        } else if (x2 < pxmin) {
//            x2 = pxmin;
//            y2 = (e->c - x2) / e->b;
//        }
//    } else // delta y is larger
//    {
//        x1 = pxmin;
//        if (s1 != 0 && s1->x > pxmin)
//            x1 = s1->x;
//        if (x1 > pxmax) {
//            x1 = pxmax;
//        }
//        y1 = e->c - e->a * x1;
//        x2 = pxmax;
//        if (s2 != 0 && s2->x < pxmax)
//            x2 = s2->x;
//        if (x2 < pxmin) {
//            x2 = pxmin;
//        }
//        y2 = e->c - e->a * x2;
//        // Never occurs according to lcov
//        // if( ((y1 > pymax) & (y2 > pymax)) | ((y1 < pymin) & (y2 < pymin)) )
//        // {
//        //     return 0;
//        // }
//        if (y1 > pymax) {
//            y1 = pymax;
//            x1 = (e->c - y1) / e->a;
//        } else if (y1 < pymin) {
//            y1 = pymin;
//            x1 = (e->c - y1) / e->a;
//        }
//        if (y2 > pymax) {
//            y2 = pymax;
//            x2 = (e->c - y2) / e->a;
//        } else if (y2 < pymin) {
//            y2 = pymin;
//            x2 = (e->c - y2) / e->a;
//        };
//    };

//    e->pos[0].x = x1;
//    e->pos[0].y = y1;
//    e->pos[1].x = x2;
//    e->pos[1].y = y2;

//    // If the two points are equal, the result is invalid
//    return (x1 == x2 && y1 == y2) ? 0 : 1;
//}

//// The line equation: ax + by + c = 0
//// see jcv_edge_create
// static int jcv_edge_clipline(jcv_context_internal* internal, jcv_edge* e)
//{
//     return internal->clipper.clip_fn(&internal->clipper, e);
// }

// static jcv_edge* jcv_edge_new(jcv_context_internal* internal, jcv_site* s1, jcv_site* s2)
//{
//     jcv_edge* e = jcv_alloc_edge(internal);
//     jcv_edge_create(e, s1, s2);
//     return e;
// }

//// jcv_halfedge

// static void jcv_halfedge_link(jcv_halfedge* edge, jcv_halfedge* newedge)
//{
//     newedge->left = edge;
//     newedge->right = edge->right;
//     edge->right->left = newedge;
//     edge->right = newedge;
// }

// static inline void jcv_halfedge_unlink(jcv_halfedge* he)
//{
//     he->left->right = he->right;
//     he->right->left = he->left;
//     he->left = 0;
//     he->right = 0;
// }

// static inline jcv_halfedge* jcv_halfedge_new(jcv_context_internal* internal, jcv_edge* e, int direction)
//{
//     jcv_halfedge* he = jcv_alloc_halfedge(internal);
//     he->edge = e;
//     he->left = 0;
//     he->right = 0;
//     he->direction = direction;
//     he->pqpos = 0;
//     // These are set outside
//     //he->y
//     //he->vertex
//     return he;
// }

// static void jcv_halfedge_delete(jcv_context_internal* internal, jcv_halfedge* he)
//{
//     he->right = internal->halfedgepool;
//     internal->halfedgepool = he;
// }

// static inline jcv_site* jcv_halfedge_leftsite(const jcv_halfedge* he)
//{
//     return he->edge->sites[he->direction];
// }

// static inline jcv_site* jcv_halfedge_rightsite(const jcv_halfedge* he)
//{
//     return he->edge ? he->edge->sites[1 - he->direction] : 0;
// }

// static int jcv_halfedge_rightof(const jcv_halfedge* he, const jcv_point* p)
//{
//     const jcv_edge* e = he->edge;
//     const jcv_site* topsite = e->sites[1];

//    int right_of_site = (p->x > topsite->p.x) ? 1 : 0;
//    if (right_of_site && he->direction == JCV_DIRECTION_LEFT)
//        return 1;
//    if (!right_of_site && he->direction == JCV_DIRECTION_RIGHT)
//        return 0;

//    jcv_real dxp, dyp, dxs, t1, t2, t3, yl;

//    int above;
//    if (e->a == (jcv_real)1) {
//        dyp = p->y - topsite->p.y;
//        dxp = p->x - topsite->p.x;
//        int fast = 0;
//        if ((!right_of_site & (e->b < (jcv_real)0)) | (right_of_site & (e->b >= (jcv_real)0))) {
//            above = dyp >= e->b * dxp;
//            fast = above;
//        } else {
//            above = (p->x + p->y * e->b) > e->c;
//            if (e->b < (jcv_real)0)
//                above = !above;
//            if (!above)
//                fast = 1;
//        };
//        if (!fast) {
//            dxs = topsite->p.x - e->sites[0]->p.x;
//            above = e->b * (dxp * dxp - dyp * dyp)
//                < dxs * dyp * ((jcv_real)1 + (jcv_real)2 * dxp / dxs + e->b * e->b);
//            if (e->b < (jcv_real)0)
//                above = !above;
//        };
//    } else // e->b == 1
//    {
//        yl = e->c - e->a * p->x;
//        t1 = p->y - yl;
//        t2 = p->x - topsite->p.x;
//        t3 = yl - topsite->p.y;
//        above = t1 * t1 > (t2 * t2 + t3 * t3);
//    };
//    return (he->direction == JCV_DIRECTION_LEFT ? above : !above);
//}

//// Keeps the priority queue sorted with events sorted in ascending order
//// Return 1 if the edges needs to be swapped
// static inline int jcv_halfedge_compare(const jcv_halfedge* he1, const jcv_halfedge* he2)
//{
//     return (he1->y == he2->y) ? he1->vertex.x > he2->vertex.x : he1->y > he2->y;
// }

// static int jcv_halfedge_intersect(const jcv_halfedge* he1, const jcv_halfedge* he2, jcv_point* out)
//{
//     const jcv_edge* e1 = he1->edge;
//     const jcv_edge* e2 = he2->edge;

//    jcv_real d = e1->a * e2->b - e1->b * e2->a;
//    if (((jcv_real)-JCV_EDGE_INTERSECT_THRESHOLD < d && d < (jcv_real)JCV_EDGE_INTERSECT_THRESHOLD)) {
//        return 0;
//    }
//    out->x = (e1->c * e2->b - e1->b * e2->c) / d;
//    out->y = (e1->a * e2->c - e1->c * e2->a) / d;

//    const jcv_edge* e;
//    const jcv_halfedge* he;
//    if (jcv_point_less(&e1->sites[1]->p, &e2->sites[1]->p)) {
//        he = he1;
//        e = e1;
//    } else {
//        he = he2;
//        e = e2;
//    }

//    int right_of_site = out->x >= e->sites[1]->p.x;
//    if ((right_of_site && he->direction == JCV_DIRECTION_LEFT) || (!right_of_site && he->direction == JCV_DIRECTION_RIGHT)) {
//        return 0;
//    }

//    return 1;
//}

//// Priority queue

// static int jcv_pq_moveup(jcv_priorityqueue* pq, int pos)
//{
//     jcv_halfedge** items = (jcv_halfedge**)pq->items;
//     jcv_halfedge* node = items[pos];

//    for (int parent = (pos >> 1);
//         pos > 1 && jcv_halfedge_compare(items[parent], node);
//         pos = parent, parent = parent >> 1) {
//        items[pos] = items[parent];
//        items[pos]->pqpos = pos;
//    }

//    node->pqpos = pos;
//    items[pos] = node;
//    return pos;
//}

// static int jcv_pq_maxchild(jcv_priorityqueue* pq, int pos)
//{
//     int child = pos << 1;
//     if (child >= pq->numitems)
//         return 0;
//     jcv_halfedge** items = (jcv_halfedge**)pq->items;
//     if ((child + 1) < pq->numitems && jcv_halfedge_compare(items[child], items[child + 1]))
//         return child + 1;
//     return child;
// }

// static int jcv_pq_movedown(jcv_priorityqueue* pq, int pos)
//{
//     jcv_halfedge** items = (jcv_halfedge**)pq->items;
//     jcv_halfedge* node = items[pos];

//    int child = jcv_pq_maxchild(pq, pos);
//    while (child && jcv_halfedge_compare(node, items[child])) {
//        items[pos] = items[child];
//        items[pos]->pqpos = pos;
//        pos = child;
//        child = jcv_pq_maxchild(pq, pos);
//    }

//    items[pos] = node;
//    items[pos]->pqpos = pos;
//    return pos;
//}

// static void jcv_pq_create(jcv_priorityqueue* pq, int capacity, void** buffer)
//{
//     pq->maxnumitems = capacity;
//     pq->numitems = 1;
//     pq->items = buffer;
// }

// static int jcv_pq_empty(jcv_priorityqueue* pq)
//{
//     return pq->numitems == 1 ? 1 : 0;
// }

// static int jcv_pq_push(jcv_priorityqueue* pq, void* node)
//{
//     assert(pq->numitems < pq->maxnumitems);
//     int n = pq->numitems++;
//     pq->items[n] = node;
//     return jcv_pq_moveup(pq, n);
// }

// static void* jcv_pq_pop(jcv_priorityqueue* pq)
//{
//     void* node = pq->items[1];
//     pq->items[1] = pq->items[--pq->numitems];
//     jcv_pq_movedown(pq, 1);
//     return node;
// }

// static void* jcv_pq_top(jcv_priorityqueue* pq)
//{
//     return pq->items[1];
// }

// static void jcv_pq_remove(jcv_priorityqueue* pq, jcv_halfedge* node)
//{
//     if (pq->numitems == 1)
//         return;
//     int pos = node->pqpos;
//     if (pos == 0)
//         return;

//    jcv_halfedge** items = (jcv_halfedge**)pq->items;

//    items[pos] = items[--pq->numitems];
//    if (jcv_halfedge_compare(node, items[pos]))
//        jcv_pq_moveup(pq, pos);
//    else
//        jcv_pq_movedown(pq, pos);
//    node->pqpos = pos;
//}

//// internal functions

// static inline jcv_site* jcv_nextsite(jcv_context_internal* internal)
//{
//     return (internal->currentsite < internal->numsites) ? &internal->sites[internal->currentsite++] : 0;
// }

// static jcv_halfedge* jcv_get_edge_above_x(jcv_context_internal* internal, const jcv_point* p)
//{
//     // Gets the arc on the beach line at the x coordinate (i.e. right above the new site event)

//    // A good guess it's close by (Can be optimized)
//    jcv_halfedge* he = internal->last_inserted;
//    if (!he) {
//        if (p->x < (internal->rect.max.x - internal->rect.min.x) / 2)
//            he = internal->beachline_start;
//        else
//            he = internal->beachline_end;
//    }

//    //
//    if (he == internal->beachline_start || (he != internal->beachline_end && jcv_halfedge_rightof(he, p))) {
//        do {
//            he = he->right;
//        } while (he != internal->beachline_end && jcv_halfedge_rightof(he, p));

//        he = he->left;
//    } else {
//        do {
//            he = he->left;
//        } while (he != internal->beachline_start && !jcv_halfedge_rightof(he, p));
//    }

//    return he;
//}

// static int jcv_check_circle_event(const jcv_halfedge* he1, const jcv_halfedge* he2, jcv_point* vertex)
//{
//     jcv_edge* e1 = he1->edge;
//     jcv_edge* e2 = he2->edge;
//     if (e1 == 0 || e2 == 0 || e1->sites[1] == e2->sites[1]) {
//         return 0;
//     }

//    return jcv_halfedge_intersect(he1, he2, vertex);
//}

// static void jcv_site_event(jcv_context_internal* internal, jcv_site* site)
//{
//     jcv_halfedge* left = jcv_get_edge_above_x(internal, &site->p);
//     jcv_halfedge* right = left->right;
//     jcv_site* bottom = jcv_halfedge_rightsite(left);
//     if (!bottom)
//         bottom = internal->bottomsite;

//    jcv_edge* edge = jcv_edge_new(internal, bottom, site);
//    edge->next = internal->edges;
//    internal->edges = edge;

//    jcv_halfedge* edge1 = jcv_halfedge_new(internal, edge, JCV_DIRECTION_LEFT);
//    jcv_halfedge* edge2 = jcv_halfedge_new(internal, edge, JCV_DIRECTION_RIGHT);

//    jcv_halfedge_link(left, edge1);
//    jcv_halfedge_link(edge1, edge2);

//    internal->last_inserted = right;

//    jcv_point p;
//    if (jcv_check_circle_event(left, edge1, &p)) {
//        jcv_pq_remove(internal->eventqueue, left);
//        left->vertex = p;
//        left->y = p.y + jcv_point_dist(&site->p, &p);
//        jcv_pq_push(internal->eventqueue, left);
//    }
//    if (jcv_check_circle_event(edge2, right, &p)) {
//        edge2->vertex = p;
//        edge2->y = p.y + jcv_point_dist(&site->p, &p);
//        jcv_pq_push(internal->eventqueue, edge2);
//    }
//}

//// https://cp-algorithms.com/geometry/oriented-triangle-area.html
// static inline jcv_real jcv_determinant(const jcv_point* a, const jcv_point* b, const jcv_point* c)
//{
//     return (b->x - a->x) * (c->y - a->y) - (b->y - a->y) * (c->x - a->x);
// }

// static inline jcv_real jcv_calc_sort_metric(const jcv_site* site, const jcv_graphedge* edge)
//{
//     // We take the average of the two points, since we can better distinguish between very small edges
//     jcv_real half = 1 / (jcv_real)2;
//     jcv_real x = (edge->pos[0].x + edge->pos[1].x) * half;
//     jcv_real y = (edge->pos[0].y + edge->pos[1].y) * half;
//     jcv_real diffy = y - site->p.y;
//     jcv_real angle = JCV_ATAN2(diffy, x - site->p.x);
//     if (diffy < 0)
//         angle = angle + 2 * JCV_PI;
//     return (jcv_real)angle;
// }

// static void jcv_sortedges_insert(jcv_site* site, jcv_graphedge* edge)
//{
//     // Special case for the head end
//     if (site->edges == 0 || site->edges->angle >= edge->angle) {
//         edge->next = site->edges;
//         site->edges = edge;
//     } else {
//         // Locate the node before the point of insertion
//         jcv_graphedge* current = site->edges;
//         while (current->next != 0 && current->next->angle < edge->angle) {
//             current = current->next;
//         }
//         edge->next = current->next;
//         current->next = edge;
//     }
// }

// static void jcv_finishline(jcv_context_internal* internal, jcv_edge* e)
//{
//     if (!jcv_edge_clipline(internal, e)) {
//         return;
//     }

//    // Make sure the graph edges are CCW
//    int flip = jcv_determinant(&e->sites[0]->p, &e->pos[0], &e->pos[1]) > (jcv_real)0 ? 0 : 1;

//    for (int i = 0; i < 2; ++i) {
//        jcv_graphedge* ge = jcv_alloc_graphedge(internal);

//        ge->edge = e;
//        ge->next = 0;
//        ge->neighbor = e->sites[1 - i];
//        ge->pos[flip] = e->pos[i];
//        ge->pos[1 - flip] = e->pos[1 - i];
//        ge->angle = jcv_calc_sort_metric(e->sites[i], ge);

//        jcv_sortedges_insert(e->sites[i], ge);

//        // check that we didn't accidentally add a duplicate (rare), then remove it
//        if (ge->next && ge->angle == ge->next->angle) {
//            if (jcv_point_eq(&ge->pos[0], &ge->next->pos[0]) && jcv_point_eq(&ge->pos[1], &ge->next->pos[1])) {
//                ge->next = ge->next->next; // Throw it away, they're so few anyways
//            }
//        }
//    }
//}

// static void jcv_endpos(jcv_context_internal* internal, jcv_edge* e, const jcv_point* p, int direction)
//{
//     e->pos[direction] = *p;

//    if (!jcv_is_valid(&e->pos[1 - direction]))
//        return;

//    jcv_finishline(internal, e);
//}

// static inline void jcv_create_corner_edge(jcv_context_internal* internal, const jcv_site* site, jcv_graphedge* current, jcv_graphedge* gap)
//{
//     gap->neighbor = 0;
//     gap->pos[0] = current->pos[1];

//    if (current->pos[1].x < internal->rect.max.x && current->pos[1].y == internal->rect.min.y) {
//        gap->pos[1].x = internal->rect.max.x;
//        gap->pos[1].y = internal->rect.min.y;
//    } else if (current->pos[1].x > internal->rect.min.x && current->pos[1].y == internal->rect.max.y) {
//        gap->pos[1].x = internal->rect.min.x;
//        gap->pos[1].y = internal->rect.max.y;
//    } else if (current->pos[1].y > internal->rect.min.y && current->pos[1].x == internal->rect.min.x) {
//        gap->pos[1].x = internal->rect.min.x;
//        gap->pos[1].y = internal->rect.min.y;
//    } else if (current->pos[1].y < internal->rect.max.y && current->pos[1].x == internal->rect.max.x) {
//        gap->pos[1].x = internal->rect.max.x;
//        gap->pos[1].y = internal->rect.max.y;
//    }

//    gap->angle = jcv_calc_sort_metric(site, gap);
//}

// static jcv_edge* jcv_create_gap_edge(jcv_context_internal* internal, jcv_site* site, jcv_graphedge* ge)
//{
//     jcv_edge* edge = jcv_alloc_edge(internal);
//     edge->pos[0] = ge->pos[0];
//     edge->pos[1] = ge->pos[1];
//     edge->sites[0] = site;
//     edge->sites[1] = 0;
//     edge->a = edge->b = edge->c = 0;
//     edge->next = internal->edges;
//     internal->edges = edge;
//     return edge;
// }

// void jcv_boxshape_fillgaps(const jcv_clipper* clipper, jcv_context_internal* allocator, jcv_site* site)
//{
//     // They're sorted CCW, so if the current->pos[1] != next->pos[0], then we have a gap
//     jcv_graphedge* current = site->edges;
//     if (!current) {
//         // No edges, then it should be a single cell
//         assert(allocator->numsites == 1);

//        jcv_graphedge* gap = jcv_alloc_graphedge(allocator);
//        gap->neighbor = 0;
//        gap->pos[0] = clipper->min;
//        gap->pos[1].x = clipper->max.x;
//        gap->pos[1].y = clipper->min.y;
//        gap->angle = jcv_calc_sort_metric(site, gap);
//        gap->next = 0;
//        gap->edge = jcv_create_gap_edge(allocator, site, gap);

//        current = gap;
//        site->edges = gap;
//    }

//    jcv_graphedge* next = current->next;
//    if (!next) {
//        // Only one edge, then we assume it's a corner gap
//        jcv_graphedge* gap = jcv_alloc_graphedge(allocator);
//        jcv_create_corner_edge(allocator, site, current, gap);
//        gap->edge = jcv_create_gap_edge(allocator, site, gap);

//        gap->next = current->next;
//        current->next = gap;
//        current = gap;
//        next = site->edges;
//    }

//    while (current && next) {
//        if (jcv_point_on_box_edge(&current->pos[1], &clipper->min, &clipper->max) && !jcv_point_eq(&current->pos[1], &next->pos[0])) {
//            // Border gap
//            if (current->pos[1].x == next->pos[0].x || current->pos[1].y == next->pos[0].y) {
//                jcv_graphedge* gap = jcv_alloc_graphedge(allocator);
//                gap->neighbor = 0;
//                gap->pos[0] = current->pos[1];
//                gap->pos[1] = next->pos[0];
//                gap->angle = jcv_calc_sort_metric(site, gap);
//                gap->edge = jcv_create_gap_edge(allocator, site, gap);

//                gap->next = current->next;
//                current->next = gap;
//            } else if (jcv_point_on_box_edge(&current->pos[1], &clipper->min, &clipper->max) && jcv_point_on_box_edge(&next->pos[0], &clipper->min, &clipper->max)) {
//                jcv_graphedge* gap = jcv_alloc_graphedge(allocator);
//                jcv_create_corner_edge(allocator, site, current, gap);
//                gap->edge = jcv_create_gap_edge(allocator, site, gap);
//                gap->next = current->next;
//                current->next = gap;
//            } else {
//                // something went wrong, abort instead of looping indefinitely
//                break;
//            }
//        }

//        current = current->next;
//        if (current) {
//            next = current->next;
//            if (!next)
//                next = site->edges;
//        }
//    }
//}

//// Since the algorithm leaves gaps at the borders/corner, we want to fill them
// static void jcv_fillgaps(jcv_diagram* diagram)
//{
//     jcv_context_internal* internal = diagram->internal;
//     if (!internal->clipper.fill_fn)
//         return;

//    for (int i = 0; i < internal->numsites; ++i) {
//        jcv_site* site = &internal->sites[i];
//        internal->clipper.fill_fn(&internal->clipper, internal, site);
//    }
//}

// static void jcv_circle_event(jcv_context_internal* internal)
//{
//     jcv_halfedge* left = (jcv_halfedge*)jcv_pq_pop(internal->eventqueue);

//    jcv_halfedge* leftleft = left->left;
//    jcv_halfedge* right = left->right;
//    jcv_halfedge* rightright = right->right;
//    jcv_site* bottom = jcv_halfedge_leftsite(left);
//    jcv_site* top = jcv_halfedge_rightsite(right);

//    jcv_point vertex = left->vertex;
//    jcv_endpos(internal, left->edge, &vertex, left->direction);
//    jcv_endpos(internal, right->edge, &vertex, right->direction);

//    internal->last_inserted = rightright;

//    jcv_pq_remove(internal->eventqueue, right);
//    jcv_halfedge_unlink(left);
//    jcv_halfedge_unlink(right);
//    jcv_halfedge_delete(internal, left);
//    jcv_halfedge_delete(internal, right);

//    int direction = JCV_DIRECTION_LEFT;
//    if (bottom->p.y > top->p.y) {
//        jcv_site* temp = bottom;
//        bottom = top;
//        top = temp;
//        direction = JCV_DIRECTION_RIGHT;
//    }

//    jcv_edge* edge = jcv_edge_new(internal, bottom, top);
//    edge->next = internal->edges;
//    internal->edges = edge;

//    jcv_halfedge* he = jcv_halfedge_new(internal, edge, direction);
//    jcv_halfedge_link(leftleft, he);
//    jcv_endpos(internal, edge, &vertex, JCV_DIRECTION_RIGHT - direction);

//    jcv_point p;
//    if (jcv_check_circle_event(leftleft, he, &p)) {
//        jcv_pq_remove(internal->eventqueue, leftleft);
//        leftleft->vertex = p;
//        leftleft->y = p.y + jcv_point_dist(&bottom->p, &p);
//        jcv_pq_push(internal->eventqueue, leftleft);
//    }
//    if (jcv_check_circle_event(he, rightright, &p)) {
//        he->vertex = p;
//        he->y = p.y + jcv_point_dist(&bottom->p, &p);
//        jcv_pq_push(internal->eventqueue, he);
//    }
//}

// static inline jcv_real jcv_floor(jcv_real v)
//{
//     jcv_real i = (jcv_real)(int)v;
//     return (v < i) ? i - 1 : i;
// }

// static inline jcv_real jcv_ceil(jcv_real v)
//{
//     jcv_real i = (jcv_real)(int)v;
//     return (v > i) ? i + 1 : i;
// }

// static inline jcv_real jcv_min(jcv_real a, jcv_real b)
//{
//     return a < b ? a : b;
// }

// static inline jcv_real jcv_max(jcv_real a, jcv_real b)
//{
//     return a > b ? a : b;
// }

// void jcv_diagragenerate_(int nupoints_, const jcv_point* points, const jcv_rect* rect, const jcv_clipper* clipper, jcv_diagram* d)
//{
//     jcv_diagragenerate_useralloc_(nupoints_, points, rect, clipper, 0, jcv_alloc_fn, jcv_free_fn, d);
// }

// typedef union _jcv_cast_align_struct {
//     char* charp;
//     void** voidpp;
// } jcv_cast_align_struct;

// static inline void jcv_rect_union(jcv_rect* rect, const jcv_point* p)
//{
//     rect->min.x = jcv_min(rect->min.x, p->x);
//     rect->min.y = jcv_min(rect->min.y, p->y);
//     rect->max.x = jcv_max(rect->max.x, p->x);
//     rect->max.y = jcv_max(rect->max.y, p->y);
// }

// static inline void jcv_rect_round(jcv_rect* rect)
//{
//     rect->min.x = jcv_floor(rect->min.x);
//     rect->min.y = jcv_floor(rect->min.y);
//     rect->max.x = jcv_ceil(rect->max.x);
//     rect->max.y = jcv_ceil(rect->max.y);
// }

// static inline void jcv_rect_inflate(jcv_rect* rect, jcv_real amount)
//{
//     rect->min.x -= amount;
//     rect->min.y -= amount;
//     rect->max.x += amount;
//     rect->max.y += amount;
// }

// static int jcv_prune_duplicates(jcv_context_internal* internal, jcv_rect* rect)
//{
//     int nusites_ = internal->numsites;
//     jcv_site* sites = internal->sites;

//    jcv_rect r;
//    r.min.x = r.min.y = JCV_FLT_MAX;
//    r.max.x = r.max.y = -JCV_FLT_MAX;

//    int offset = 0;
//    // Prune duplicates first
//    for (int i = 0; i < nusites_; i++) {
//        const jcv_site* s = &sites[i];
//        // Remove duplicates, to avoid anomalies
//        if (i > 0 && jcv_point_eq(&s->p, &sites[i - 1].p)) {
//            offset++;
//            continue;
//        }

//        sites[i - offset] = sites[i];

//        jcv_rect_union(&r, &s->p);
//    }
//    internal->numsites -= offset;
//    if (rect) {
//        *rect = r;
//    }
//    return offset;
//}

// static int jcv_prune_not_in_shape(jcv_context_internal* internal, jcv_rect* rect)
//{
//     int nusites_ = internal->numsites;
//     jcv_site* sites = internal->sites;

//    jcv_rect r;
//    r.min.x = r.min.y = JCV_FLT_MAX;
//    r.max.x = r.max.y = -JCV_FLT_MAX;

//    int offset = 0;
//    for (int i = 0; i < nusites_; i++) {
//        const jcv_site* s = &sites[i];

//        if (!internal->clipper.test_fn(&internal->clipper, s->p)) {
//            offset++;
//            continue;
//        }

//        sites[i - offset] = sites[i];

//        jcv_rect_union(&r, &s->p);
//    }
//    internal->numsites -= offset;
//    if (rect) {
//        *rect = r;
//    }
//    return offset;
//}

// static jcv_context_internal* jcv_alloc_internal(int nupoints_, void* userallocctx, FJCVAllocFn allocfn, FJCVFreeFn freefn)
//{
//     // Interesting limits from Euler's equation
//     // Slide 81: https://courses.cs.washington.edu/courses/csep521/01au/lectures/lecture10slides.pdf
//     // Page 3: https://sites.cs.ucsb.edu/~suri/cs235/Voronoi.pdf
//     int max_nuevents_ = nupoints_ * 2; // beachline can have max 2*n-5 parabolas
//     size_t sitessize = (size_t)nupoints_ * sizeof(jcv_site);
//     size_t memsize = 8u + (size_t)max_nuevents_ * sizeof(void*) + sizeof(jcv_priorityqueue) + sitessize + sizeof(jcv_context_internal);

//    char* originalmem = (char*)allocfn(userallocctx, memsize);
//    memset(originalmem, 0, memsize);

//    // align memory
//    char* mem = originalmem + 8 - ((size_t)(originalmem)&0x7);

//    jcv_context_internal* internal = (jcv_context_internal*)mem;
//    mem += sizeof(jcv_context_internal);

//    internal->mem = originalmem;
//    internal->memctx = userallocctx;
//    internal->alloc = allocfn;
//    internal->free = freefn;

//    internal->sites = (jcv_site*)mem;
//    mem += sitessize;

//    internal->eventqueue = (jcv_priorityqueue*)mem;
//    mem += sizeof(jcv_priorityqueue);

//    jcv_cast_align_struct tmp;
//    tmp.charp = mem;
//    internal->eventmem = tmp.voidpp;

//    return internal;
//}

// void jcv_diagragenerate_useralloc_(int nupoints_, const jcv_point* points, const jcv_rect* rect, const jcv_clipper* clipper, void* userallocctx, FJCVAllocFn allocfn, FJCVFreeFn freefn, jcv_diagram* d)
//{
//     if (d->internal)
//         jcv_diagrafree_(d);

//    jcv_context_internal* internal = jcv_alloc_internal(nupoints_, userallocctx, allocfn, freefn);

//    internal->beachline_start = jcv_halfedge_new(internal, 0, 0);
//    internal->beachline_end = jcv_halfedge_new(internal, 0, 0);

//    internal->beachline_start->left = 0;
//    internal->beachline_start->right = internal->beachline_end;
//    internal->beachline_end->left = internal->beachline_start;
//    internal->beachline_end->right = 0;

//    internal->last_inserted = 0;

//    int max_nuevents_ = nupoints_ * 2; // beachline can have max 2*n-5 parabolas
//    jcv_pq_create(internal->eventqueue, max_nuevents_, (void**)internal->eventmem);

//    internal->numsites = nupoints_;
//    jcv_site* sites = internal->sites;

//    for (int i = 0; i < nupoints_; ++i) {
//        sites[i].p = points[i];
//        sites[i].edges = 0;
//        sites[i].index = i;
//    }

//    qsort(sites, (size_t)nupoints_, sizeof(jcv_site), jcv_point_cmp);

//    jcv_clipper box_clipper;
//    if (clipper == 0) {
//        box_clipper.test_fn = jcv_boxshape_test;
//        box_clipper.clip_fn = jcv_boxshape_clip;
//        box_clipper.fill_fn = jcv_boxshape_fillgaps;
//        clipper = &box_clipper;
//    }
//    internal->clipper = *clipper;

//    jcv_rect tmp_rect;
//    tmp_rect.min.x = tmp_rect.min.y = JCV_FLT_MAX;
//    tmp_rect.max.x = tmp_rect.max.y = -JCV_FLT_MAX;
//    jcv_prune_duplicates(internal, &tmp_rect);

//    // Prune using the test second
//    if (internal->clipper.test_fn) {
//        // e.g. used by the box clipper in the test_fn
//        internal->clipper.min = rect ? rect->min : tmp_rect.min;
//        internal->clipper.max = rect ? rect->max : tmp_rect.max;

//        jcv_prune_not_in_shape(internal, &tmp_rect);

//        // The pruning might have made the bounding box smaller
//        if (!rect) {
//            // In the case of all sites being all on a horizontal or vertical line, the
//            // rect area will be zero, and the diagram generation will most likely fail
//            jcv_rect_round(&tmp_rect);
//            jcv_rect_inflate(&tmp_rect, 10);

//            internal->clipper.min = tmp_rect.min;
//            internal->clipper.max = tmp_rect.max;
//        }
//    }

//    internal->rect = rect ? *rect : tmp_rect;

//    d->min = internal->rect.min;
//    d->max = internal->rect.max;
//    d->numsites = internal->numsites;
//    d->internal = internal;

//    internal->bottomsite = jcv_nextsite(internal);

//    jcv_priorityqueue* pq = internal->eventqueue;
//    jcv_site* site = jcv_nextsite(internal);

//    int finished = 0;
//    while (!finished) {
//        jcv_point lowest_pq_point;
//        if (!jcv_pq_empty(pq)) {
//            jcv_halfedge* he = (jcv_halfedge*)jcv_pq_top(pq);
//            lowest_pq_point.x = he->vertex.x;
//            lowest_pq_point.y = he->y;
//        }

//        if (site != 0 && (jcv_pq_empty(pq) || jcv_point_less(&site->p, &lowest_pq_point))) {
//            jcv_site_event(internal, site);
//            site = jcv_nextsite(internal);
//        } else if (!jcv_pq_empty(pq)) {
//            jcv_circle_event(internal);
//        } else {
//            finished = 1;
//        }
//    }

//    for (jcv_halfedge* he = internal->beachline_start->right; he != internal->beachline_end; he = he->right) {
//        jcv_finishline(internal, he->edge);
//    }

//    jcv_fillgaps(d);
//}

#include "jc_voronoi.h"
#include "clipper_types.h"
#include "memory.h"

// INTERNAL FUNCTIONS

#if defined(_MSC_VER) && !defined(__cplusplus)
    #define inline __inline
#endif

// jcv_point

static inline int jcv_point_cmp(const void* p1, const void* p2) {
    const jcv_point* s1 = (const jcv_point*)p1;
    const jcv_point* s2 = (const jcv_point*)p2;
    return (s1->y != s2->y) ? (s1->y < s2->y ? -1 : 1) : (s1->x < s2->x ? -1 : 1);
}

static inline int jcv_point_less(const jcv_point* pt1, const jcv_point* pt2) {
    return (pt1->y == pt2->y) ? (pt1->x < pt2->x) : pt1->y < pt2->y;
}

static inline int jcv_point_eq(const jcv_point* pt1, const jcv_point* pt2) {
    return (pt1->y == pt2->y) && (pt1->x == pt2->x);
}

static inline int jcv_point_on_edge(const jcv_point* pt, const jcv_point* min, const jcv_point* max) {
    return pt->x == min->x || pt->y == min->y || pt->x == max->x || pt->y == max->y;
}

static inline jcv_real jcv_point_dist_sq(const jcv_point* pt1, const jcv_point* pt2) {
    jcv_real diffx = pt1->x - pt2->x;
    jcv_real diffy = pt1->y - pt2->y;
    return diffx * diffx + diffy * diffy;
}

static inline jcv_real jcv_point_dist(const jcv_point* pt1, const jcv_point* pt2) {
    return (jcv_real)(JCV_SQRT(jcv_point_dist_sq(pt1, pt2)));
}

// Structs

#pragma pack(push, 1)

typedef struct _jcv_halfedge {
    jcv_edge* edge;
    struct _jcv_halfedge* left;
    struct _jcv_halfedge* right;
    jcv_point vertex;
    jcv_real y;
    int direction; // 0=left, 1=right
    int pqpos;
} jcv_halfedge;

typedef struct _jcv_memoryblock {
    size_t sizefree;
    struct _jcv_memoryblock* next;
    char* memory;
} jcv_memoryblock;

typedef int (*FJCVPriorityQueuePrint)(const void* node, int pos);

typedef struct _jcv_priorityqueue {
    // Implements a binary heap
    int maxnumitems;
    int numitems;
    void** items;
} jcv_priorityqueue;

typedef struct _jcv_context_internal {
    void* mem;
    jcv_edge* edges;
    jcv_halfedge* beachline_start;
    jcv_halfedge* beachline_end;
    jcv_halfedge* last_inserted;
    jcv_priorityqueue* eventqueue;

    jcv_site* sites;
    jcv_site* bottomsite;
    int numsites;
    int numsites_sqrt;
    int currentsite;
    int _padding;

    jcv_memoryblock* memblocks;
    jcv_edge* edgepool;
    jcv_halfedge* halfedgepool;
    void** eventmem;

    void* memctx; // Given by the user
    FJCVAllocFn alloc;
    FJCVFreeFn free;

    jcv_point min;
    jcv_point max;
} jcv_context_internal;

#pragma pack(pop)

static const int JCV_DIRECTION_LEFT = 0;
static const int JCV_DIRECTION_RIGHT = 1;
static const jcv_real JCV_INVALID_VALUE = (jcv_real)-JCV_FLT_MAX;

void jcv_diagrafree_(jcv_diagram* d) {
    jcv_context_internal* internal = d->internal;
    void* memctx = internal->memctx;
    FJCVFreeFn freefn = internal->free;
    while (internal->memblocks) {
        jcv_memoryblock* p = internal->memblocks;
        internal->memblocks = internal->memblocks->next;
        freefn(memctx, p);
    }

    freefn(memctx, internal->mem);
}

const jcv_site* jcv_diagraget_sites_(const jcv_diagram* diagram) {
    return diagram->internal->sites;
}

const jcv_edge* jcv_diagraget_edges_(const jcv_diagram* diagram) {
    return diagram->internal->edges;
}

const jcv_edge* jcv_diagraget_next_edge_(const jcv_edge* edge) {
    const jcv_edge* e = edge->next;
    while (e != nullptr && jcv_point_eq(&e->pos[0], &e->pos[1])) {
        e = e->next;
    }
    return e;
}

static void* jcv_alloc(jcv_context_internal* internal, size_t size) {
    if (!internal->memblocks || internal->memblocks->sizefree < size) {
        size_t blocksize = 16 * 1024;
        jcv_memoryblock* block = (jcv_memoryblock*)internal->alloc(internal->memctx, blocksize);
        size_t offset = sizeof(jcv_memoryblock);
        block->sizefree = blocksize - offset;
        block->next = internal->memblocks;
        block->memory = ((char*)block) + offset;
        internal->memblocks = block;
    }
    void* p = internal->memblocks->memory;
    internal->memblocks->memory += size;
    internal->memblocks->sizefree -= size;
    return p;
}

static jcv_edge* jcv_alloc_edge(jcv_context_internal* internal) {
    return (jcv_edge*)jcv_alloc(internal, sizeof(jcv_edge));
}

static jcv_halfedge* jcv_alloc_halfedge(jcv_context_internal* internal) {
    if (internal->halfedgepool) {
        jcv_halfedge* edge = internal->halfedgepool;
        internal->halfedgepool = internal->halfedgepool->right;
        return edge;
    }

    return (jcv_halfedge*)jcv_alloc(internal, sizeof(jcv_halfedge));
}

static jcv_graphedge* jcv_alloc_graphedge(jcv_context_internal* internal) {
    return (jcv_graphedge*)jcv_alloc(internal, sizeof(jcv_graphedge));
}

static void* jcv_alloc_fn(void* memctx, size_t size) {
    (void)memctx;
    return malloc(size);
}

static void jcv_free_fn(void* memctx, void* p) {
    (void)memctx;
    free(p);
}

// jcv_edge

static inline int jcv_is_valid(const jcv_point* p) {
    return (p->x != JCV_INVALID_VALUE || p->y != JCV_INVALID_VALUE) ? 1 : 0;
}

static void jcv_edge_create(jcv_edge* e, jcv_site* s1, jcv_site* s2) {
    e->next = 0;
    e->sites[0] = s1;
    e->sites[1] = s2;
    e->pos[0].x = JCV_INVALID_VALUE;
    e->pos[0].y = JCV_INVALID_VALUE;
    e->pos[1].x = JCV_INVALID_VALUE;
    e->pos[1].y = JCV_INVALID_VALUE;

    // Create line equation between S1 and S2:
    // jcv_real a = -1 * (s2->p.y - s1->p.y);
    // jcv_real b = s2->p.x - s1->p.x;
    // //jcv_real c = -1 * (s2->p.x - s1->p.x) * s1->p.y + (s2->p.y - s1->p.y) * s1->p.x;
    //
    // // create perpendicular line
    // jcv_real pa = b;
    // jcv_real pb = -a;
    // //jcv_real pc = pa * s1->p.x + pb * s1->p.y;
    //
    // // Move to the mid point
    // jcv_real mx = s1->p.x + dx * jcv_real(0.5);
    // jcv_real my = s1->p.y + dy * jcv_real(0.5);
    // jcv_real pc = ( pa * mx + pb * my );

    jcv_real dx = s2->p.x - s1->p.x;
    jcv_real dy = s2->p.y - s1->p.y;
    int dx_is_larger = (dx * dx) > (dy * dy); // instead of fabs

    // Simplify it, using dx and dy
    e->c = dx * (s1->p.x + dx * (jcv_real)0.5) + dy * (s1->p.y + dy * (jcv_real)0.5);

    if (dx_is_larger) {
        e->a = (jcv_real)1;
        e->b = dy / dx;
        e->c /= dx;
    } else {
        e->a = dx / dy;
        e->b = (jcv_real)1;
        e->c /= dy;
    }
}

static int jcv_edge_clipline(jcv_edge* e, jcv_point* min, jcv_point* max) {
    jcv_real pxmin = min->x;
    jcv_real pxmax = max->x;
    jcv_real pymin = min->y;
    jcv_real pymax = max->y;

    jcv_real x1, y1, x2, y2;
    jcv_point* s1;
    jcv_point* s2;
    if (e->a == (jcv_real)1 && e->b >= (jcv_real)0) {
        s1 = jcv_is_valid(&e->pos[1]) ? &e->pos[1] : 0;
        s2 = jcv_is_valid(&e->pos[0]) ? &e->pos[0] : 0;
    } else {
        s1 = jcv_is_valid(&e->pos[0]) ? &e->pos[0] : 0;
        s2 = jcv_is_valid(&e->pos[1]) ? &e->pos[1] : 0;
    };

    if (e->a == (jcv_real)1) {
        y1 = pymin;
        if (s1 != 0 && s1->y > pymin) {
            y1 = s1->y;
        }
        if (y1 > pymax) {
            y1 = pymax;
        }
        x1 = e->c - e->b * y1;
        y2 = pymax;
        if (s2 != 0 && s2->y < pymax)
            y2 = s2->y;

        if (y2 < pymin) {
            y2 = pymin;
        }
        x2 = (e->c) - (e->b) * y2;
        // Never occurs according to lcov
        // if( ((x1 > pxmax) & (x2 > pxmax)) | ((x1 < pxmin) & (x2 < pxmin)) )
        // {
        //     return 0;
        // }
        if (x1 > pxmax) {
            x1 = pxmax;
            y1 = (e->c - x1) / e->b;
        } else if (x1 < pxmin) {
            x1 = pxmin;
            y1 = (e->c - x1) / e->b;
        }
        if (x2 > pxmax) {
            x2 = pxmax;
            y2 = (e->c - x2) / e->b;
        } else if (x2 < pxmin) {
            x2 = pxmin;
            y2 = (e->c - x2) / e->b;
        }
    } else {
        x1 = pxmin;
        if (s1 != 0 && s1->x > pxmin)
            x1 = s1->x;
        if (x1 > pxmax) {
            x1 = pxmax;
        }
        y1 = e->c - e->a * x1;
        x2 = pxmax;
        if (s2 != 0 && s2->x < pxmax)
            x2 = s2->x;
        if (x2 < pxmin) {
            x2 = pxmin;
        }
        y2 = e->c - e->a * x2;
        // Never occurs according to lcov
        // if( ((y1 > pymax) & (y2 > pymax)) | ((y1 < pymin) & (y2 < pymin)) )
        // {
        //     return 0;
        // }
        if (y1 > pymax) {
            y1 = pymax;
            x1 = (e->c - y1) / e->a;
        } else if (y1 < pymin) {
            y1 = pymin;
            x1 = (e->c - y1) / e->a;
        }
        if (y2 > pymax) {
            y2 = pymax;
            x2 = (e->c - y2) / e->a;
        } else if (y2 < pymin) {
            y2 = pymin;
            x2 = (e->c - y2) / e->a;
        };
    };

    e->pos[0].x = x1;
    e->pos[0].y = y1;
    e->pos[1].x = x2;
    e->pos[1].y = y2;

    // If the two points are equal, the result is invalid
    return (x1 == x2 && y1 == y2) ? 0 : 1;
}

static jcv_edge* jcv_edge_new(jcv_context_internal* internal, jcv_site* s1, jcv_site* s2) {
    jcv_edge* e = jcv_alloc_edge(internal);
    jcv_edge_create(e, s1, s2);
    return e;
}

// jcv_halfedge

static void jcv_halfedge_link(jcv_halfedge* edge, jcv_halfedge* newedge) {
    newedge->left = edge;
    newedge->right = edge->right;
    edge->right->left = newedge;
    edge->right = newedge;
}

static inline void jcv_halfedge_unlink(jcv_halfedge* he) {
    he->left->right = he->right;
    he->right->left = he->left;
    he->left = 0;
    he->right = 0;
}

static inline jcv_halfedge* jcv_halfedge_new(jcv_context_internal* internal, jcv_edge* e, int direction) {
    jcv_halfedge* he = jcv_alloc_halfedge(internal);
    he->edge = e;
    he->left = 0;
    he->right = 0;
    he->direction = direction;
    he->pqpos = 0;
    // These are set outside
    // he->y
    // he->vertex
    return he;
}

static void jcv_halfedge_delete(jcv_context_internal* internal, jcv_halfedge* he) {
    he->right = internal->halfedgepool;
    internal->halfedgepool = he;
}

static inline jcv_site* jcv_halfedge_leftsite(const jcv_halfedge* he) {
    return he->edge->sites[he->direction];
}

static inline jcv_site* jcv_halfedge_rightsite(const jcv_halfedge* he) {
    return he->edge ? he->edge->sites[1 - he->direction] : 0;
}

static int jcv_halfedge_rightof(const jcv_halfedge* he, const jcv_point* p) {
    const jcv_edge* e = he->edge;
    const jcv_site* topsite = e->sites[1];

    int right_of_site = (p->x > topsite->p.x) ? 1 : 0;
    if (right_of_site && he->direction == JCV_DIRECTION_LEFT)
        return 1;
    if (!right_of_site && he->direction == JCV_DIRECTION_RIGHT)
        return 0;

    jcv_real dxp, dyp, dxs, t1, t2, t3, yl;

    int above;
    if (e->a == (jcv_real)1) {
        dyp = p->y - topsite->p.y;
        dxp = p->x - topsite->p.x;
        int fast = 0;
        if ((!right_of_site & (e->b < (jcv_real)0)) | (right_of_site & (e->b >= (jcv_real)0))) {
            above = dyp >= e->b * dxp;
            fast = above;
        } else {
            above = (p->x + p->y * e->b) > e->c;
            if (e->b < (jcv_real)0)
                above = !above;
            if (!above)
                fast = 1;
        };
        if (!fast) {
            dxs = topsite->p.x - e->sites[0]->p.x;
            above = e->b * (dxp * dxp - dyp * dyp)
                < dxs * dyp * ((jcv_real)1 + (jcv_real)2 * dxp / dxs + e->b * e->b);
            if (e->b < (jcv_real)0)
                above = !above;
        };
    } else // e->b == 1
    {
        yl = e->c - e->a * p->x;
        t1 = p->y - yl;
        t2 = p->x - topsite->p.x;
        t3 = yl - topsite->p.y;
        above = t1 * t1 > (t2 * t2 + t3 * t3);
    };
    return (he->direction == JCV_DIRECTION_LEFT ? above : !above);
}

// Keeps the priority queue sorted with events sorted in ascending order
// Return 1 if the edges needs to be swapped
static inline int jcv_halfedge_compare(const jcv_halfedge* he1, const jcv_halfedge* he2) {
    return (he1->y == he2->y) ? he1->vertex.x > he2->vertex.x : he1->y > he2->y;
}

static int jcv_halfedge_intersect(const jcv_halfedge* he1, const jcv_halfedge* he2, jcv_point* out) {
    const jcv_edge* e1 = he1->edge;
    const jcv_edge* e2 = he2->edge;

    jcv_real d = e1->a * e2->b - e1->b * e2->a;
    if (((jcv_real)-JCV_EDGE_INTERSECT_THRESHOLD < d && d < (jcv_real)JCV_EDGE_INTERSECT_THRESHOLD)) {
        return 0;
    }
    out->x = (e1->c * e2->b - e1->b * e2->c) / d;
    out->y = (e1->a * e2->c - e1->c * e2->a) / d;

    const jcv_edge* e;
    const jcv_halfedge* he;
    if (jcv_point_less(&e1->sites[1]->p, &e2->sites[1]->p)) {
        he = he1;
        e = e1;
    } else {
        he = he2;
        e = e2;
    }

    int right_of_site = out->x >= e->sites[1]->p.x;
    if ((right_of_site && he->direction == JCV_DIRECTION_LEFT) || (!right_of_site && he->direction == JCV_DIRECTION_RIGHT)) {
        return 0;
    }

    return 1;
}

// Priority queue

static int jcv_pq_moveup(jcv_priorityqueue* pq, int pos) {
    jcv_halfedge** items = (jcv_halfedge**)pq->items;
    jcv_halfedge* node = items[pos];

    for (int parent = (pos >> 1);
         pos > 1 && jcv_halfedge_compare(items[parent], node);
         pos = parent, parent = parent >> 1) {
        items[pos] = items[parent];
        items[pos]->pqpos = pos;
    }

    node->pqpos = pos;
    items[pos] = node;
    return pos;
}

static int jcv_pq_maxchild(jcv_priorityqueue* pq, int pos) {
    int child = pos << 1;
    if (child >= pq->numitems)
        return 0;
    jcv_halfedge** items = (jcv_halfedge**)pq->items;
    if ((child + 1) < pq->numitems && jcv_halfedge_compare(items[child], items[child + 1]))
        return child + 1;
    return child;
}

static int jcv_pq_movedown(jcv_priorityqueue* pq, int pos) {
    jcv_halfedge** items = (jcv_halfedge**)pq->items;
    jcv_halfedge* node = items[pos];

    int child = jcv_pq_maxchild(pq, pos);
    while (child && jcv_halfedge_compare(node, items[child])) {
        items[pos] = items[child];
        items[pos]->pqpos = pos;
        pos = child;
        child = jcv_pq_maxchild(pq, pos);
    }

    items[pos] = node;
    items[pos]->pqpos = pos;
    return pos;
}

static void jcv_pq_create(jcv_priorityqueue* pq, int capacity, void** buffer) {
    pq->maxnumitems = capacity;
    pq->numitems = 1;
    pq->items = buffer;
}

static int jcv_pq_empty(jcv_priorityqueue* pq) {
    return pq->numitems == 1 ? 1 : 0;
}

static int jcv_pq_push(jcv_priorityqueue* pq, void* node) {
    assert(pq->numitems < pq->maxnumitems);
    int n = pq->numitems++;
    pq->items[n] = node;
    return jcv_pq_moveup(pq, n);
}

static void* jcv_pq_pop(jcv_priorityqueue* pq) {
    void* node = pq->items[1];
    pq->items[1] = pq->items[--pq->numitems];
    jcv_pq_movedown(pq, 1);
    return node;
}

static void* jcv_pq_top(jcv_priorityqueue* pq) {
    return pq->items[1];
}

static void jcv_pq_remove(jcv_priorityqueue* pq, jcv_halfedge* node) {
    if (pq->numitems == 1)
        return;
    int pos = node->pqpos;
    if (pos == 0)
        return;

    jcv_halfedge** items = (jcv_halfedge**)pq->items;

    items[pos] = items[--pq->numitems];
    if (jcv_halfedge_compare(node, items[pos]))
        jcv_pq_moveup(pq, pos);
    else
        jcv_pq_movedown(pq, pos);
    node->pqpos = pos;
}

// internal functions

static inline jcv_site* jcv_nextsite(jcv_context_internal* internal) {
    return (internal->currentsite < internal->numsites) ? &internal->sites[internal->currentsite++] : 0;
}

static jcv_halfedge* jcv_get_edge_above_x(jcv_context_internal* internal, const jcv_point* p) {
    // Gets the arc on the beach line at the x coordinate (i.e. right above the new site event)

    // A good guess it's close by (Can be optimized)
    jcv_halfedge* he = internal->last_inserted;
    if (!he) {
        if (p->x < (internal->max.x - internal->min.x) / 2)
            he = internal->beachline_start;
        else
            he = internal->beachline_end;
    }

    //
    if (he == internal->beachline_start || (he != internal->beachline_end && jcv_halfedge_rightof(he, p))) {
        do {
            he = he->right;
        } while (he != internal->beachline_end && jcv_halfedge_rightof(he, p));

        he = he->left;
    } else {
        do {
            he = he->left;
        } while (he != internal->beachline_start && !jcv_halfedge_rightof(he, p));
    }

    return he;
}

static int jcv_check_circle_event(const jcv_halfedge* he1, const jcv_halfedge* he2, jcv_point* vertex) {
    jcv_edge* e1 = he1->edge;
    jcv_edge* e2 = he2->edge;
    if (e1 == 0 || e2 == 0 || e1->sites[1] == e2->sites[1]) {
        return 0;
    }

    return jcv_halfedge_intersect(he1, he2, vertex);
}

static void jcv_site_event(jcv_context_internal* internal, jcv_site* site) {
    jcv_halfedge* left = jcv_get_edge_above_x(internal, &site->p);
    jcv_halfedge* right = left->right;
    jcv_site* bottom = jcv_halfedge_rightsite(left);
    if (!bottom)
        bottom = internal->bottomsite;

    jcv_edge* edge = jcv_edge_new(internal, bottom, site);
    edge->next = internal->edges;
    internal->edges = edge;

    jcv_halfedge* edge1 = jcv_halfedge_new(internal, edge, JCV_DIRECTION_LEFT);
    jcv_halfedge* edge2 = jcv_halfedge_new(internal, edge, JCV_DIRECTION_RIGHT);

    jcv_halfedge_link(left, edge1);
    jcv_halfedge_link(edge1, edge2);

    internal->last_inserted = right;

    jcv_point p;
    if (jcv_check_circle_event(left, edge1, &p)) {
        jcv_pq_remove(internal->eventqueue, left);
        left->vertex = p;
        left->y = p.y + jcv_point_dist(&site->p, &p);
        jcv_pq_push(internal->eventqueue, left);
    }
    if (jcv_check_circle_event(edge2, right, &p)) {
        edge2->vertex = p;
        edge2->y = p.y + jcv_point_dist(&site->p, &p);
        jcv_pq_push(internal->eventqueue, edge2);
    }
}

// https://cp-algorithms.com/geometry/oriented-triangle-area.html
static inline jcv_real jcv_determinant(const jcv_point* a, const jcv_point* b, const jcv_point* c) {
    return (b->x - a->x) * (c->y - a->y) - (b->y - a->y) * (c->x - a->x);
}

static inline jcv_real jcv_calc_sort_metric(const jcv_site* site, const jcv_graphedge* edge) {
    // We take the average of the two points, since we can better distinguish between very small edges
    jcv_real half = 1 / (jcv_real)2;
    jcv_real x = (edge->pos[0].x + edge->pos[1].x) * half;
    jcv_real y = (edge->pos[0].y + edge->pos[1].y) * half;
    jcv_real diffy = y - site->p.y;
    jcv_real angle = JCV_ATAN2(diffy, x - site->p.x);
    if (diffy < 0)
        angle = angle + 2 * JCV_PI;
    return (jcv_real)angle;
}

static void jcv_sortedges_insert(jcv_site* site, jcv_graphedge* edge) {
    // Special case for the head end
    if (site->edges == 0 || site->edges->angle >= edge->angle) {
        edge->next = site->edges;
        site->edges = edge;
    } else {
        // Locate the node before the point of insertion
        jcv_graphedge* current = site->edges;
        while (current->next != 0 && current->next->angle < edge->angle) {
            current = current->next;
        }
        edge->next = current->next;
        current->next = edge;
    }
}

static void jcv_finishline(jcv_context_internal* internal, jcv_edge* e) {
    if (!jcv_edge_clipline(e, &internal->min, &internal->max))
        return;

    // Make sure the graph edges are CCW
    int flip = jcv_determinant(&e->sites[0]->p, &e->pos[0], &e->pos[1]) > (jcv_real)0 ? 0 : 1;

    for (int i = 0; i < 2; ++i) {
        jcv_graphedge* ge = jcv_alloc_graphedge(internal);

        ge->edge = e;
        ge->next = 0;
        ge->neighbor = e->sites[1 - i];
        ge->pos[flip] = e->pos[i];
        ge->pos[1 - flip] = e->pos[1 - i];
        ge->angle = jcv_calc_sort_metric(e->sites[i], ge);

        jcv_sortedges_insert(e->sites[i], ge);

        // check that we didn't accidentally add a duplicate (rare), then remove it
        if (ge->next && ge->angle == ge->next->angle) {
            if (jcv_point_eq(&ge->pos[0], &ge->next->pos[0]) && jcv_point_eq(&ge->pos[1], &ge->next->pos[1])) {
                ge->next = ge->next->next; // Throw it away, they're so few anyways
            }
        }
    }
}

static void jcv_endpos(jcv_context_internal* internal, jcv_edge* e, const jcv_point* p, int direction) {
    e->pos[direction] = *p;

    if (!jcv_is_valid(&e->pos[1 - direction]))
        return;

    jcv_finishline(internal, e);
}

static inline void jcv_create_corner_edge(jcv_context_internal* internal, const jcv_site* site, jcv_graphedge* current, jcv_graphedge* gap) {
    gap->neighbor = 0;
    gap->pos[0] = current->pos[1];

    if (current->pos[1].x < internal->max.x && current->pos[1].y == internal->min.y) {
        gap->pos[1].x = internal->max.x;
        gap->pos[1].y = internal->min.y;
    } else if (current->pos[1].x > internal->min.x && current->pos[1].y == internal->max.y) {
        gap->pos[1].x = internal->min.x;
        gap->pos[1].y = internal->max.y;
    } else if (current->pos[1].y > internal->min.y && current->pos[1].x == internal->min.x) {
        gap->pos[1].x = internal->min.x;
        gap->pos[1].y = internal->min.y;
    } else if (current->pos[1].y < internal->max.y && current->pos[1].x == internal->max.x) {
        gap->pos[1].x = internal->max.x;
        gap->pos[1].y = internal->max.y;
    }

    gap->angle = jcv_calc_sort_metric(site, gap);
}

static jcv_edge* jcv_create_gap_edge(jcv_context_internal* internal, jcv_site* site, jcv_graphedge* ge) {
    jcv_edge* edge = jcv_alloc_edge(internal);
    edge->pos[0] = ge->pos[0];
    edge->pos[1] = ge->pos[1];
    edge->sites[0] = site;
    edge->sites[1] = 0;
    edge->a = edge->b = edge->c = 0;
    edge->next = internal->edges;
    internal->edges = edge;
    return edge;
}

// Since the algorithm leaves gaps at the borders/corner, we want to fill them
static void jcv_fillgaps(jcv_diagram* diagram) {
    jcv_context_internal* internal = diagram->internal;
    for (int i = 0; i < internal->numsites; ++i) {
        ProgressCancel::incCurrent();
        jcv_site* site = &internal->sites[i];

        // They're sorted CCW, so if the current->pos[1] != next->pos[0], then we have a gap
        jcv_graphedge* current = site->edges;
        if (!current) {
            // No edges, then it should be a single cell
            assert(internal->numsites == 1);

            jcv_graphedge* gap = jcv_alloc_graphedge(internal);
            gap->neighbor = 0;
            gap->pos[0] = internal->min;
            gap->pos[1].x = internal->max.x;
            gap->pos[1].y = internal->min.y;
            gap->angle = jcv_calc_sort_metric(site, gap);
            gap->next = 0;
            gap->edge = jcv_create_gap_edge(internal, site, gap);

            current = gap;
            site->edges = gap;
        }

        jcv_graphedge* next = current->next;
        if (!next) {
            // Only one edge, then we assume it's a corner gap
            jcv_graphedge* gap = jcv_alloc_graphedge(internal);
            jcv_create_corner_edge(internal, site, current, gap);
            gap->edge = jcv_create_gap_edge(internal, site, gap);

            gap->next = current->next;
            current->next = gap;
            current = gap;
            next = site->edges;
        }

        while (current && next) {
            if (jcv_point_on_edge(&current->pos[1], &diagram->min, &diagram->max) && !jcv_point_eq(&current->pos[1], &next->pos[0])) {
                // Border gap
                if (current->pos[1].x == next->pos[0].x || current->pos[1].y == next->pos[0].y) {
                    jcv_graphedge* gap = jcv_alloc_graphedge(internal);
                    gap->neighbor = 0;
                    gap->pos[0] = current->pos[1];
                    gap->pos[1] = next->pos[0];
                    gap->angle = jcv_calc_sort_metric(site, gap);
                    gap->edge = jcv_create_gap_edge(internal, site, gap);

                    gap->next = current->next;
                    current->next = gap;
                } else if (jcv_point_on_edge(&current->pos[1], &diagram->min, &diagram->max) && jcv_point_on_edge(&next->pos[0], &diagram->min, &diagram->max)) {
                    jcv_graphedge* gap = jcv_alloc_graphedge(internal);
                    jcv_create_corner_edge(internal, site, current, gap);
                    gap->edge = jcv_create_gap_edge(internal, site, gap);
                    gap->next = current->next;
                    current->next = gap;
                } else {
                    // something went wrong, abort instead of looping indefinitely
                    break;
                }
            }

            current = current->next;
            if (current) {
                next = current->next;
                if (!next)
                    next = site->edges;
            }
        }
    }
}

static void jcv_circle_event(jcv_context_internal* internal) {
    jcv_halfedge* left = (jcv_halfedge*)jcv_pq_pop(internal->eventqueue);

    jcv_halfedge* leftleft = left->left;
    jcv_halfedge* right = left->right;
    jcv_halfedge* rightright = right->right;
    jcv_site* bottom = jcv_halfedge_leftsite(left);
    jcv_site* top = jcv_halfedge_rightsite(right);

    jcv_point vertex = left->vertex;
    jcv_endpos(internal, left->edge, &vertex, left->direction);
    jcv_endpos(internal, right->edge, &vertex, right->direction);

    internal->last_inserted = rightright;

    jcv_pq_remove(internal->eventqueue, right);
    jcv_halfedge_unlink(left);
    jcv_halfedge_unlink(right);
    jcv_halfedge_delete(internal, left);
    jcv_halfedge_delete(internal, right);

    int direction = JCV_DIRECTION_LEFT;
    if (bottom->p.y > top->p.y) {
        jcv_site* temp = bottom;
        bottom = top;
        top = temp;
        direction = JCV_DIRECTION_RIGHT;
    }

    jcv_edge* edge = jcv_edge_new(internal, bottom, top);
    edge->next = internal->edges;
    internal->edges = edge;

    jcv_halfedge* he = jcv_halfedge_new(internal, edge, direction);
    jcv_halfedge_link(leftleft, he);
    jcv_endpos(internal, edge, &vertex, JCV_DIRECTION_RIGHT - direction);

    jcv_point p;
    if (jcv_check_circle_event(leftleft, he, &p)) {
        jcv_pq_remove(internal->eventqueue, leftleft);
        leftleft->vertex = p;
        leftleft->y = p.y + jcv_point_dist(&bottom->p, &p);
        jcv_pq_push(internal->eventqueue, leftleft);
    }
    if (jcv_check_circle_event(he, rightright, &p)) {
        he->vertex = p;
        he->y = p.y + jcv_point_dist(&bottom->p, &p);
        jcv_pq_push(internal->eventqueue, he);
    }
}

static inline jcv_real jcv_floor(jcv_real v) {
    jcv_real i = (jcv_real)(int)v;
    return (v < i) ? i - 1 : i;
}

static inline jcv_real jcv_ceil(jcv_real v) {
    jcv_real i = (jcv_real)(int)v;
    return (v > i) ? i + 1 : i;
}

static inline void _jcv_calc_bounds(int nupoints_, const jcv_point* points, jcv_point* min, jcv_point* max) {
    jcv_point _min = points[0];
    jcv_point _max = points[0];
    for (int i = 1; i < nupoints_; ++i) {
        if (points[i].x < _min.x)
            _min.x = points[i].x;
        else if (points[i].x > _max.x)
            _max.x = points[i].x;

        if (points[i].y < _min.y)
            _min.y = points[i].y;
        else if (points[i].y > _max.y)
            _max.y = points[i].y;
    }
    min->x = jcv_floor(_min.x);
    min->y = jcv_floor(_min.y);
    max->x = jcv_ceil(_max.x);
    max->y = jcv_ceil(_max.y);
}

void jcv_diagragenerate_(size_t nupoints_, const jcv_point* points, const jcv_rect* rect, void*, jcv_diagram* d) {
    jcv_diagragenerate_useralloc_(nupoints_, points, rect, 0, jcv_alloc_fn, jcv_free_fn, d);
}

typedef union _jcv_cast_align_struct {
    char* charp;
    void** voidpp;
} jcv_cast_align_struct;

void jcv_diagragenerate_useralloc_(size_t nupoints_, const jcv_point* points, const jcv_rect* rect, void* userallocctx, FJCVAllocFn allocfn, FJCVFreeFn freefn, jcv_diagram* d) {
    if (d->internal)
        jcv_diagrafree_(d);

    size_t max_nuevents_ = nupoints_ * 2; // beachline can have max 2*n-5 parabolas
    size_t sitessize = (size_t)nupoints_ * sizeof(jcv_site);
    size_t memsize = 8u + (size_t)max_nuevents_ * sizeof(void*) + sizeof(jcv_priorityqueue) + sitessize + sizeof(jcv_context_internal);

    char* originalmem = (char*)allocfn(userallocctx, memsize);
    memset(originalmem, 0, memsize);

    // align memory
    char* mem = originalmem + 8 - ((size_t)(originalmem)&0x7);

    jcv_context_internal* internal = (jcv_context_internal*)mem;
    mem += sizeof(jcv_context_internal);

    internal->mem = originalmem;
    internal->memctx = userallocctx;
    internal->alloc = allocfn;
    internal->free = freefn;

    internal->beachline_start = jcv_halfedge_new(internal, 0, 0);
    internal->beachline_end = jcv_halfedge_new(internal, 0, 0);

    internal->beachline_start->left = 0;
    internal->beachline_start->right = internal->beachline_end;
    internal->beachline_end->left = internal->beachline_start;
    internal->beachline_end->right = 0;

    internal->last_inserted = 0;

    internal->sites = (jcv_site*)mem;
    mem += sitessize;

    internal->eventqueue = (jcv_priorityqueue*)mem;
    mem += sizeof(jcv_priorityqueue);

    jcv_cast_align_struct tmp;
    tmp.charp = mem;
    internal->eventmem = tmp.voidpp;

#pragma warning(push)
#pragma warning(disable : 4267) // possible loss of data
    jcv_pq_create(internal->eventqueue, max_nuevents_, (void**)internal->eventmem);

    jcv_site* sites = internal->sites;

    for (size_t i = 0; i < nupoints_; ++i) {
        sites[i].p = points[i];
        sites[i].edges = 0;
        sites[i].index = i;
    }

    qsort(sites, (size_t)nupoints_, sizeof(jcv_site), jcv_point_cmp);

    int offset = 0;
    for (size_t i = 0; i < nupoints_; i++) {
        const jcv_site* s = &sites[i];
        // Remove duplicates, to avoid anomalies
        if (i > 0 && jcv_point_eq(&s->p, &sites[i - 1].p)) {
            offset++;
            continue;
        }
        // Remove points outside of the bounding box to avoid bad edge clipping later on
        if (rect != 0) {
            if (s->p.x < rect->min.x || s->p.x > rect->max.x || s->p.y < rect->min.y || s->p.y > rect->max.y) {
                offset++;
                continue;
            }
        }

        sites[i - offset] = sites[i];
    }
    nupoints_ -= offset;
    ProgressCancel::setMax(nupoints_ * 3);
    ProgressCancel::setCurrent(0);
    if (rect == 0) {
        _jcv_calc_bounds(nupoints_, points, &d->min, &d->max);
        d->min.x -= 10;
        d->min.y -= 10;
        d->max.x += 10;
        d->max.y += 10;
    } else {
        d->min = rect->min;
        d->max = rect->max;
    }
    internal->min = d->min;
    internal->max = d->max;

    d->internal = internal;
    d->numsites = nupoints_;

    internal->numsites = nupoints_;
    internal->numsites_sqrt = (int)(JCV_SQRT((jcv_real)nupoints_));
    internal->currentsite = 0;

#pragma warning(pop)

    internal->bottomsite = jcv_nextsite(internal);

    jcv_priorityqueue* pq = internal->eventqueue;
    jcv_site* site = jcv_nextsite(internal);

    int finished = 0;
    while (!finished) {
        ProgressCancel::incCurrent();
        jcv_point lowest_pq_point;
        if (!jcv_pq_empty(pq)) {
            jcv_halfedge* he = (jcv_halfedge*)jcv_pq_top(pq);
            lowest_pq_point.x = he->vertex.x;
            lowest_pq_point.y = he->y;
        }

        if (site != 0 && (jcv_pq_empty(pq) || jcv_point_less(&site->p, &lowest_pq_point))) {
            jcv_site_event(internal, site);
            site = jcv_nextsite(internal);
        } else if (!jcv_pq_empty(pq)) {
            jcv_circle_event(internal);
        } else {
            finished = 1;
        }
    }

    for (jcv_halfedge* he = internal->beachline_start->right; he != internal->beachline_end; he = he->right) {
        ProgressCancel::incCurrent();
        jcv_finishline(internal, he->edge);
    }

    jcv_fillgaps(d);
}
