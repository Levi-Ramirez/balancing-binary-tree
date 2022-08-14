// ============================================================================
// File: PrecondViolatedExcept.h
// ============================================================================
// Header file for the class PrecondViolatedExcept
// ============================================================================

#ifndef PRECONDVIOLATEDEXCEPT_HEADER
#define PRECONDVIOLATEDEXCEPT_HEADER

class PrecondViolatedExcept
{
    public:
        PrecondViolatedExcept(std::string errorMsg);

        std::string 	GetMsg() const;
        void			SetMsg(std::string	errorMsg);

    private:
        std::string		m_errorMsg;

};

#endif
