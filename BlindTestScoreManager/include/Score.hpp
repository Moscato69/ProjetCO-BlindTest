#ifndef __SCORE_HPP__
#define __SCORE_HPP__

#include <cstdint>
/**
 *  @brief  Score basic class 
 */

class Score
{
private:
    uint16_t    Points{0};  /** Actual number of points */

    /**
     * @brief : Points accessor (w)
     * @param uint16_t Nb - Number of points to set
     */
    void setPoints(uint16_t Nb) noexcept {this->Points = Nb;};    
    
public:
    /** 
     * @brief default ctor - defaulted 
     * */
    Score() = default;  


    /**
     * @brief Standard Ctor
     * @param initialPoints 
     */
    explicit Score(uint16_t initialPoints)noexcept:Points{initialPoints}{}; 

    /**
     * @brief Dtor - Defaulted
     */
    virtual ~Score() = default;

    /**
     * @brief   Points accessor (w)
     * @return  uint16_t : Number of points
     */
    uint16_t getPoints() noexcept {return this->Points;};


    /**
     * @brief   reset points function
     *          Sets the number of points to zero 
     */
    void    reset() noexcept {this->setPoints(0);};

    /**
     * @brief Sets the number of points to a defined value
     * @param uint16_t Nb : number of points 
     */
    void    set(uint16_t Nb) noexcept {this->setPoints(Nb);};

    /**
     * @brief Increments the number of points by a certain value (1 by default) 
     * @param uint16_t Value 
     */
    void    inc(uint16_t Value = 1)noexcept{this->setPoints(this->getPoints() + Value);};

    /**
     * @brief Decrementss the number of points by a certain value (1 by default) 
     * @param uint16_t Value 
     */
    void    dec(uint16_t Value = 1) noexcept;

};




#endif  /*  __SCORE_HPP__   */